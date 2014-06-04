/*
 * program:  xbounce.c
 * purpose:  show basic X11 programming
 * details:  X11 version of the bounce1d program
 * compile:
 *
 *   cc xbounce.c alarmlib.c -lX11 -o xbounce
 *
 *   on GNU/Linux, you probably need:
 *   cc xbounce.c alarmlib.c -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -o xbounce
 */
/* INCLUDE FILES */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include	<stdio.h>
#include	<signal.h>
// #include <stdlib.h>

#define	INIT_TICKS_PER_SEC	150
#define TABLE_HEIGHT		6
#define	BALL_HEIGHT		10
#define	BALL_WIDTH		10

/* =============================================================================*/

/* PROTOTYPES */
void initializePaddle();
void initializeBall();
void initializeWalls();
void ball_move();
void draw_walls();
void draw_paddle();
void serve();
int  bounce_or_lose();
void change_speed();
int  randomInRange(int min, int max);

/*
 * global settings
 */

Display           *mydisplay;
Window            mywindow;
GC                mygc;
int               myscreen;
unsigned int      width, height;
unsigned long     myforeground, mybackground;
int               ticks_per_sec;
int		  ball_x, ball_y, ball_height, ball_width, ball_dir;

/* =============================================================================*/

main(int argc, char **argv)
{
	XEvent      myevent;
	KeySym      mykey;
	XSizeHints  myhint;
	int         i, done;
	char        text[10];

	/* FOR XGETGEOMETRY */
	int         x, y, border_width, depth;
	Window      rootwin;

	char *welcomeMsg = "Welcome to xbounce";
	srand(getpid());

	/* SETUP X ENVIRONMENT */
	mydisplay = XOpenDisplay( "" );
	myscreen  = DefaultScreen( mydisplay );
	myhint.x  = 200, myhint.y = 300;
	myhint.width = 350, myhint.height = 250;
	myhint.flags = PPosition | PSize;

	myforeground = BlackPixel( mydisplay, myscreen );
	mybackground = WhitePixel( mydisplay, myscreen );

	mywindow = XCreateSimpleWindow(mydisplay, RootWindow(mydisplay, myscreen),
               myhint.x, myhint.y, myhint.width, myhint.height,
               5, myforeground, mybackground);

	mygc = XCreateGC( mydisplay, mywindow, 0, 0 );
	XSetBackground( mydisplay, mygc, mybackground);
	XSetForeground( mydisplay, mygc, myforeground);

	XSelectInput( mydisplay, mywindow, 
				ButtonPressMask|KeyPressMask|ExposureMask);

	XMapRaised( mydisplay, mywindow );

	/*
	 * Get height and width of window
	 */

	rootwin = RootWindow(mydisplay, myscreen);
	XGetGeometry(mydisplay, mywindow, &rootwin,
		&x, &y, &width, &height, &border_width, &depth );

	/*
	 * Sleep a second then show message
	 */
	sleep(1);

	XDrawString( mydisplay, mywindow, mygc, 120 , height/2, 
		welcomeMsg, strlen(welcomeMsg));
	XFlush(mydisplay);

	sleep(2); /* give a chance to see the initial message */

	start_action();

	done=0;
	while( !done )
	{
		XNextEvent( mydisplay, &myevent ); 
		signal( SIGALRM , SIG_IGN );
		switch( myevent.type )
		{
			case Expose:
				show_fixed();
				break;

			case MappingNotify:
				XRefreshKeyboardMapping( (XMappingEvent *)&myevent );
				break;

			case ButtonPress:
				break;

			case KeyPress:
				i = XLookupString((XKeyEvent *)&myevent,
						text,10,&mykey,0);
				if( i==1 && (text[0]=='q'||text[0]=='Q' )  )
					done = 1;
				else if ( i==1 && text[0]=='s')
					slower();
				else if ( i==1 && text[0]=='f')
					faster();
				else if ( i==1 && text[0]==' ')
					bounce();
				break;
		}
		signal( SIGALRM , ball_move );
	}

	/* wrap up */
	XFreeGC( mydisplay, mygc );
	XDestroyWindow( mydisplay, mywindow );
	XCloseDisplay( mydisplay );
	return 0;
}

/* =============================================================================*/
/*
 * start_action
 * 
 * purpose: turn on ticker and start game going
 */

start_action()
{
	void ball_move(int);

	ball_height = BALL_HEIGHT;
	ball_width  = BALL_WIDTH;
	ball_x = width/2;
	ball_y = height/2 - ball_height;
	ball_dir = +1;

	XClearWindow(mydisplay, mywindow);
	draw_surface();
	XFlush(mydisplay);

	signal(SIGALRM, ball_move);
	ticks_per_sec = INIT_TICKS_PER_SEC;
	set_ticker( 1000 / ticks_per_sec );   /* send millisecs per tick */
}
draw_directions()
{
	char	msg[] = "SPACE=bounce, Q=quit, s=slower, f=faster";

	XDrawString( mydisplay, mywindow, mygc, 10 , (3*height)/4,
			msg, strlen(msg));
	XFlush(mydisplay);
}

show_fixed()
{
	draw_surface();
	draw_directions();
}
/*
 * draw table top
 */
draw_surface()
{
	/* set the color to FG */
	XSetForeground( mydisplay, mygc, myforeground);
	XFillRectangle(mydisplay, mywindow, mygc,
			0, height/2+1,
			width, TABLE_HEIGHT);
}

void ball_move(int s)
{
	signal(SIGALRM, SIG_IGN);
	if ( ball_x + ball_dir + ball_width > width )
		ball_dir = -1;
	if ( ball_x <= 0 )
		ball_dir = +1;

	/* blank out the previous ball position */
	XSetForeground( mydisplay, mygc, mybackground);
	XFillArc(mydisplay, mywindow, mygc, ball_x, ball_y,
		 ball_width, ball_height, 0, 360 * 64 );

	/* draw the new ball position */
	ball_x += ball_dir;
	XSetForeground( mydisplay, mygc, myforeground);
	XFillArc(mydisplay, mywindow, mygc, ball_x, ball_y,
		 ball_width, ball_height, 0, 360 * 64 );
	XFlush(mydisplay);
	signal(SIGALRM, ball_move);
	printf("%3d %3d\r", ball_x, ball_y);
	fflush(stdout);
}

/*
 * decrease number of ticks per second
 */
slower()
{
	if ( ticks_per_sec > 4 ){
		ticks_per_sec /= 2;
	}
	set_ticker(1000/ticks_per_sec);
}

faster()
{
	ticks_per_sec *= 2;
	if ( ticks_per_sec > 1000 )
		ticks_per_sec = 1000;
	set_ticker(1000/ticks_per_sec);
}

bounce()
{
	ball_dir = -ball_dir;
}
