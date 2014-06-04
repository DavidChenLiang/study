#include	<stdio.h>
#include	<signal.h>
#include	<curses.h>
#include	<termios.h>

/*
 * box.c
 *
 *	purpose: show how a screen-oriented program can respond to 
 *		 window resizing
 *	action:  draw a box that just fits into the window and 
 *		 count seconds in the center of the box.  
 *		 On SIGWINCH, re-read window size and redraw
 *		 on SIGINT, close up and go
 */

struct termios ttystate;

main()
{
	void	byebye();
	void	resize();
	int	n = 0;

	tcgetattr(0,&ttystate);
	signal( SIGINT,   byebye );
	signal( SIGWINCH, resize );
	initscr();
	drawbox();

	while(1)
	{
		move(LINES/2,COLS/2);
		printw("%2d", n++);
		move(LINES-1,COLS-1);
		refresh();
		sleep(1);
	}
}

drawbox()
{
	int	i;

	clear();
	for(i = 1; i<COLS-1; i++ ){
		move(1,i); addch('*');
		move(LINES-2,i); addch('*');
	}
	for(i = 1; i<LINES-1; i++ ){
		move(i,1); addch('*');
		move(i,COLS-2); addch('*');
	}
	refresh();
}

void
resize()
{
	endwin();
	initscr();
	drawbox();
}

void
byebye()
{
	move(LINES-1,0);
	refresh();
	endwin();
	tcsetattr(0,TCSADRAIN,&ttystate);
	exit(0);
}
