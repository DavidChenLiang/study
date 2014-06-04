
/* =============================================================================

PROGRAM      : X PONG   

AUTHOR       : Gary Baker 

DATE         : April 8, 1999

PURPOSE      : the video game pong programmed in X windows.

CREDITS      : alarmlib.c used as is from Prof. Molay.
               bounce2d.c and bounce.h from Prof. Molay adapted for pong.
               Prof Molay's version of helloworld for Xwindows also adapted.
               Other X code from "Xlib Programming Manual for Version 11"
               by Adrain Nye ( O'Reilly & Associates )

/* =============================================================================*/

/* INCLUDE FILES */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <signal.h>
#include <stdlib.h>
#include "pong.h"

/* =============================================================================*/

/* PROTOTYPES */
void initializePaddle();
void initializeBall();
void initializeWalls();
void down_paddle();
void up_paddle();
void ball_move();
void draw_walls();
void draw_paddle();
void serve();
int  bounce_or_lose();
void change_speed();
int  randomInRange(int min, int max);

/* =============================================================================*/

/* GLOBALS */
struct pongBall   theBall;
struct pongPaddle thePaddle;
struct pongWall   theWalls;
Display           *mydisplay;
Window            mywindow;
GC                mygc;
int               myscreen;
int               balls_left = 3;
unsigned int      width, height;
unsigned long     myforeground, mybackground;
int               ticksPerSecond;

/* =============================================================================*/

main( int argc, char **argv )
{
   XEvent      myevent;
   KeySym      mykey;
   XSizeHints  myhint;
   int         i, done;
   char        text[10];

   /* FOR XGETGEOMETRY */
   int         x, y, border_width, depth;
   Window      rootwin;

   char *welcomeMsg = "Welcome To X-Pong";
   srand(getpid());

   /* SETUP X ENVIRONMENT */
   mydisplay = XOpenDisplay( "" );
   myscreen  = DefaultScreen( mydisplay );
   myhint.x  = 200, myhint.y = 300;
   myhint.width = 350, myhint.height = 250;
   myhint.flags = PPosition | PSize;

   myforeground = BlackPixel( mydisplay, myscreen );
   mybackground = WhitePixel( mydisplay, myscreen );

   mywindow = XCreateSimpleWindow( mydisplay, RootWindow( mydisplay, myscreen ),
               myhint.x, myhint.y, myhint.width, myhint.height,
               5, myforeground, mybackground );

   mygc = XCreateGC( mydisplay, mywindow, 0, 0 );
   XSetBackground( mydisplay, mygc, mybackground);
   XSetForeground( mydisplay, mygc, myforeground);

   XSelectInput( mydisplay, mywindow, ButtonPressMask|KeyPressMask|ExposureMask);

   XMapRaised( mydisplay, mywindow );

   /* GET THE HEIGHT AND WIDTH OF THE WINDOW */
   rootwin = RootWindow(mydisplay, myscreen);
   XGetGeometry(mydisplay, mywindow, &rootwin,
      &x, &y, &width, &height, &border_width, &depth );

   /* for some reason I can't get my initial text to  */
   /* display if I don't sleep first ??  	      */
   sleep(1);

   /* strings positions currently hard coded because at the moment I don't know
   ** how to figure out the length of a string in pixels */
   XDrawString( mydisplay, mywindow, mygc, 120 , height/2, 
		welcomeMsg, strlen(welcomeMsg));
   XFlush(mydisplay);
   sleep(2); /* give a chance to see the initial message */
   serve();

   done=0;
   do
   {
      XNextEvent( mydisplay, &myevent ); 

      signal( SIGALRM , SIG_IGN );
      switch( myevent.type )
      {

      case Expose:
         break;

      case MappingNotify:
         XRefreshKeyboardMapping( &myevent );
         break;

      case ButtonPress:
         break;

      case KeyPress:
         i = XLookupString( &myevent, text, 10, &mykey, 0 );
         if( i==1 && text[0]=='q' )
            done = 1;
         else if ( i==1 && text[0]=='j')
            down_paddle(height);
         else if ( i==1 && text[0]=='k')
            up_paddle();
         break;
      }
      signal( SIGALRM, ball_move );

   } while( done==0 );

   /* wrap up */
   XFreeGC( mydisplay, mygc );
   XDestroyWindow( mydisplay, mywindow );
   XCloseDisplay( mydisplay );
   exit( 0 );
}

/* =============================================================================*/
void serve()
{
   char * serveMessage = "BALLS REMAINING"; 
   char * youLoseMsg = "You Lose !";
   int msgLength   = strlen(serveMessage);
   char numLeftAsString[2];

   if ( balls_left == 0 )
   {
      /* show message you lose, then exit */
      XClearWindow(mydisplay, mywindow);
      XDrawString( mydisplay, mywindow, mygc,
         width/4 + 20 , height/2, youLoseMsg, strlen(youLoseMsg));
      XFlush(mydisplay);
      sleep(2);
      exit(0);
   }

   /* print the number of balls remaining */
   sprintf(numLeftAsString, "%d", balls_left);
   XClearWindow(mydisplay, mywindow);
   XDrawString( mydisplay, mywindow, mygc,
      width/4 - 20  , height/2, numLeftAsString , 2);
   XDrawString( mydisplay, mywindow, mygc,
      width/4 , height/2, serveMessage, strlen( serveMessage ));
   XFlush(mydisplay);
   sleep(2);

   XClearWindow(mydisplay, mywindow);
   initializeBall();
   initializeWalls();
   initializePaddle();

   balls_left--;

   signal( SIGALRM, ball_move );
   ticksPerSecond = INIT_TICKS_PER_SEC;
   set_ticker( 1000 / ticksPerSecond );   /* send millisecs per tick */
}


/* =============================================================================*/

void initializeBall()
{
   int aRandomNum;

   /* BALL STARTS CENTER COURT */
   theBall.y_pos = height / 2;
   theBall.x_pos = width  / 2;

   /* RANDOM X SPEED */
   theBall.x_ttm = theBall.x_ttg = randomInRange(MIN_TTM, MAX_TTM);

   /* RANDOM Y SPEED */
   theBall.y_ttm = theBall.y_ttg = randomInRange(MIN_TTM, MAX_TTM);

   /* RANDOM X DIRECTION */
   if ( random () & 1 ) theBall.x_dir = 1;
   else theBall.x_dir = -1;

   /* RANDOM Y DIRECTION */
   if ( random () & 1 ) theBall.y_dir = 1;
   else theBall.y_dir = -1;
}

/* =============================================================================*/

void initializePaddle()
{
   thePaddle.pad_top = ( height / 2 ) - ( PADDLE_LENGTH / 2 );
   thePaddle.pad_bot = thePaddle.pad_top + PADDLE_LENGTH;
   thePaddle.pad_col = theWalls.right_col;
}

/* =============================================================================*/

void initializeWalls()
{
   theWalls.left_col  = PIXELS_FROM_WIN_EDGE;
   theWalls.right_col = width - PIXELS_FROM_WIN_EDGE;
   theWalls.top_row   = PIXELS_FROM_WIN_EDGE;
   theWalls.bot_row   = height - PIXELS_FROM_WIN_EDGE;
}

/* =============================================================================*/

void draw_walls()
{
   int length_of_horiz_wall = theWalls.right_col - theWalls.left_col;
   int length_of_vert_wall  = theWalls.bot_row - theWalls.top_row;

   /* the top horiz wall */
   XFillRectangle(mydisplay, mywindow ,mygc, theWalls.left_col, theWalls.top_row,
      length_of_horiz_wall , WALL_THICKNESS);

   /* the bottom horiz wall */
   XFillRectangle(mydisplay, mywindow ,mygc, theWalls.left_col, theWalls.bot_row,
      length_of_horiz_wall , WALL_THICKNESS);

   /* the left vert wall */
   XFillRectangle(mydisplay, mywindow ,mygc, theWalls.left_col, theWalls.top_row,
      WALL_THICKNESS, length_of_vert_wall);
}

/* =============================================================================*/

void ball_move() {
   int moved = 0;
   int prevBallX = theBall.x_pos;
   int prevBallY = theBall.y_pos;

   signal( SIGALRM , SIG_IGN );

   if ( theBall.y_ttm > 0 && theBall.y_ttg-- == 1 ){
      theBall.y_pos += ( theBall.y_dir * BALL_PIXELS_TO_MOVE );
      theBall.y_ttg = theBall.y_ttm  ;
      moved = 1;
   }

   if ( theBall.x_ttm > 0 && theBall.x_ttg-- == 1 ){
      theBall.x_pos += ( theBall.x_dir * BALL_PIXELS_TO_MOVE );
      theBall.x_ttg = theBall.x_ttm  ;
      moved = 1;
   }

   if ( moved ){
      /* blank out the previous ball position */
      XSetForeground( mydisplay, mygc, mybackground);
      XFillArc(mydisplay, mywindow, mygc, prevBallX, prevBallY, 
		7, 7, 0, 360 * 64 );
      XSetForeground( mydisplay, mygc, myforeground);

      /* draw the new ball position */
      XFillArc(mydisplay, mywindow, mygc, theBall.x_pos, theBall.y_pos, 
		7, 7, 0, 360 * 64 );

      draw_walls();
      draw_paddle();
      XFlush(mydisplay);

      /* MISS */
      if ( bounce_or_lose() == -1 )
      {
         set_ticker(0);
         serve();
      }
   }
	signal( SIGALRM, ball_move);
}

/* =============================================================================*/

int bounce_or_lose() /* 0 = no contact, 1 = bounce, -1 = miss */
{
   int bounceval = 0;

   if ( theBall.y_pos <= theWalls.top_row + BALL_PIXELS_TO_MOVE ) {
      bounceval = 1;
      theBall.y_dir = 1;
   }
   else if ( theBall.y_pos >= theWalls.bot_row - BALL_PIXELS_TO_MOVE - WALL_THICKNESS ) {
      bounceval = 1;
      theBall.y_dir = -1;
   }

   if ( theBall.x_pos <= theWalls.left_col + BALL_PIXELS_TO_MOVE ) {
      bounceval = 1;
      theBall.x_dir = 1;
   }
   else if ( theBall.x_pos > thePaddle.pad_col - BALL_PIXELS_TO_MOVE - WALL_THICKNESS) {
      /* IS IT A HIT */
      if ( theBall.y_pos >= thePaddle.pad_top && theBall.y_pos <= thePaddle.pad_bot ) {
         change_speed();
         bounceval = 1;
         theBall.x_dir = -1;
      }
      /* IS A MISS */
      else { 
         bounceval = -1; 
      }
   }
   return bounceval;
}

/* =============================================================================*/

void down_paddle()
{
   signal( SIGALRM , SIG_IGN );

   /* blank out the old paddle */
   XSetForeground( mydisplay, mygc, mybackground);
   draw_paddle();
   XSetForeground( mydisplay, mygc, myforeground);

   if ( thePaddle.pad_bot < theWalls.bot_row )
   {
      thePaddle.pad_bot += PADDLE_PIXELS_TO_MOVE;
      thePaddle.pad_top += PADDLE_PIXELS_TO_MOVE;
   }
   draw_walls();
   draw_paddle();
   XFlush(mydisplay);

   if ( bounce_or_lose() == -1 )
   {
      set_ticker(0);
      serve();
   }
   else
	   signal( SIGALRM, ball_move);
}

/* =============================================================================*/

void up_paddle()
{
   signal( SIGALRM , SIG_IGN );

   /* blank out the old paddle */
   XSetForeground( mydisplay, mygc, mybackground);
   draw_paddle();
   XSetForeground( mydisplay, mygc, myforeground);

   if ( thePaddle.pad_top > theWalls.top_row )
   {
      thePaddle.pad_bot -= PADDLE_PIXELS_TO_MOVE;
      thePaddle.pad_top -= PADDLE_PIXELS_TO_MOVE;
   }
   draw_walls();
   draw_paddle();
   XFlush(mydisplay);

   if ( bounce_or_lose() == -1 )
   {
      set_ticker(0);
      serve();
   }
   else
	   signal( SIGALRM, ball_move);
}

/* =============================================================================*/

void draw_paddle()
{
   XFillRectangle(mydisplay, mywindow ,mygc, thePaddle.pad_col, thePaddle.pad_top,
      WALL_THICKNESS , PADDLE_LENGTH);
}

/* =============================================================================*/

void change_speed()
{
   /* this function is called when the ball hits the paddle, to 
   ** change the speed by some small random amount.
   */

   int xTtmChange = randomInRange(1,2);
   int yTtmChange = randomInRange(1,2);
   int xFasterOrSlower;
   int yFasterOrSlower;
   int xChange;
   int yChange;

   int origX = theBall.x_ttm;
   int origY = theBall.y_ttm;

   /* random change is going to be + or -  */
   if ( rand () & 1 ) xFasterOrSlower = 1;
   else xFasterOrSlower = -1;

   if ( rand () & 1 ) yFasterOrSlower = 1;
   else yFasterOrSlower = -1;

   xChange = xTtmChange * xFasterOrSlower;
   yChange = yTtmChange * yFasterOrSlower;

   /* if the change is going to be negative (faster), don't go below MIN_TTM */
   if ( xChange < 0 && theBall.x_ttm - xChange >= MIN_TTM )
     theBall.x_ttm = theBall.x_ttg = theBall.x_ttm + xChange;

   /* if the change is going to be positive (faster), don't go above MAX_TTM */
   if ( xChange > 0 && theBall.x_ttm + xChange <= MAX_TTM )
     theBall.x_ttm = theBall.x_ttg = theBall.x_ttm + xChange;

   /* if the change is going to be negative (slower), don't go below MIN_TTM */
   if ( yChange < -1 && theBall.y_ttm - yChange >= MIN_TTM )
     theBall.y_ttm = theBall.y_ttg = theBall.y_ttm + yChange;

   /* if the change is going to be positive (faster), don't go above MAX_TTM */
   if ( yChange > 1 && theBall.y_ttm + yChange <= MAX_TTM )
     theBall.y_ttm = theBall.y_ttg = theBall.y_ttm + yChange;
}

/* =============================================================================*/

int randomInRange(int min, int max)
{
   /* return a random number between min and max */
   return ( ( rand() % ( max - min + 1 ) ) + min);
}

/* =============================================================================*/
