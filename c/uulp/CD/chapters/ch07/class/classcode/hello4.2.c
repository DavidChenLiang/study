#include	<stdio.h>
#include	<curses.h>

/*
 * hello4.c
 *	purpose	show how to use erase, time, and draw for animation
 */

main()
{
	int	i;

	initscr();

	/*  do some screen operations	*/
		clear();
		for(i=0; i<LINES; i++ ){
			move( i, i+i );
			if ( i%2 == 1 ) standout();
			addstr("Hello, world");
			if ( i%2 == 1 ) standend();
			refresh();
			sleep(1);
			clear();
		}


	/*  wrapup			*/
		endwin();
}
