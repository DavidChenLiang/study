#include	<stdio.h>
#include	<curses.h>
#include	<signal.h>

/*
 * bounce1.c
 *	purpose	animate using curses and alarm
 *	note	the handler does the animation
 *		the main program reads keyboard input
 *	compile	cc bounce1.c alarmlib.c -lcurses -o bounce1
 */

/*
 * some global vars that main and the handler use
 */

#define	MESSAGE	" hello "

int	cur_row;	/* current row		*/
int	cur_col;	/* current column	*/
int	direction;	/* where we are going	*/

main()
{
	int	delay;		/* bigger => slower	*/
	int	ndelay;		/* new delay		*/
	int	c;		/* user input		*/
	void	on_ticker();	/* handler for timer	*/

	initscr();
	crmode();
	noecho();
	clear();

	cur_row   = 10;		/* start here		*/
	cur_col   = 0;
	direction = 1;		/* add 1 to row number	*/
	delay     = 200;	/* 1000 ms = 1 second	*/

	move(cur_row,cur_col);	/* get into position	*/
	addstr( MESSAGE );	/* note spaces		*/
	signal(SIGALRM, on_ticker );
	set_ticker( delay );

	while(1)
	{
		ndelay = 0;
		c = getch();
		if ( c == 'Q' ) break;
		if ( c == ' ' ) direction = -direction;
		if ( c == 'f' && delay > 2 ) ndelay = delay/2;
		if ( c == 's' ) ndelay = delay * 2 ;
		if ( ndelay > 0 )
			set_ticker( delay = ndelay );
	}
	endwin();
}

void
on_ticker()
{
	signal(SIGALRM, on_ticker);	/* reset, just in case	*/
	cur_col += direction;		/* move to new column	*/
	move( cur_row, cur_col );	/* then set cursor	*/
	addstr( MESSAGE );		/* redo message		*/
	refresh();			/* and show it		*/

	/*
	 * now handle borders
	 */
	if ( direction == -1 && cur_col == 0 )
		direction = 1;
	else if ( direction == 1 && cur_col+strlen(MESSAGE) >= COLS )
		direction = -1;
}
