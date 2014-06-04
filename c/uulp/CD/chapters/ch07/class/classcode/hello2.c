#include	<stdio.h>
#include	<curses.h>

/*
 * hello2.c
 *	purpose	show how to use curses functions with a loop 
 *	outline	initialize, draw stuff, wrap up
 */

main()
{
	int	i;

	initscr();

	/* part2 : do some screen operations	*/
		clear();
		for(i=0; i<LINES; i++ ){
			move( i, i+i );
			if ( i%2 == 1 ) standout();
			addstr("Hello, world");
			if ( i%2 == 1 ) standend();
		}

	/* part3 : push requests to screen	*/
		// refresh(); 
		// getch();

	/* part4 : wrapup			*/
		endwin();
}
