#include	<stdio.h>
#include	<curses.h>

/*
 * hello1.c
 *	purpose	show the minimal calls needed to use curses
 *	outline	initialize the functions, clear, move, draw, refresh, end
 */

main()
{
	/* part1 : set up package for terminal */
		initscr() ;

	/* part2 : do some screen operations	*/
		clear();
		move(10,20);				/* row10,col20	*/
		addstr("Hello, world");			/* add a string	*/
		/* move(LINES-1,0);			/* move to LL	*/

	/* part3 : push requests to screen	*/
		refresh();
		getch();

	/* part4 : wrapup			*/
		endwin();
}
