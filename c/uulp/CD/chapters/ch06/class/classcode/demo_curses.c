#include	<curses.h>

main()
{
	int	i;

	initscr();		/* sets up the system */
	clear();		/* clear screen		*/

	for(i=0;i<24;i++)
	{
		move(i,i+i);
		if ( i%2 ) standout();
		addstr( "hello");
		standend();
	}

	refresh();		/* draw screeen		*/
	endwin();		/* shut down the curses library */
}
