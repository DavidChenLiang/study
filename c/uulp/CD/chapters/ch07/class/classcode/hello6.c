#include	<curses.h>

/*
 * hello6.c
 *  bounce a message back and forth across the screen, uses millisleep()
 */

#define	LEFTEDGE	10
#define	RIGHTEDGE	30
#define	ROW		10
#define	TICKS		200			/* 200/1000 sec */

main(int ac, char *av[])
{
	char	msg[] = " Hello ";		/* notice padding spaces */
	int	dir = +1;
	int	pos = LEFTEDGE ;
	int	delay = TICKS;

	if ( ac > 1 )
		delay = atoi( av[1] );

	initscr();
	clear();

	while(1){
		move(ROW,pos);
		addstr( msg );			/* draw it */
		move(0,0);
		printw("pos = %02d", pos);
		refresh();
		pos += dir;			/* advance position	*/
		if ( pos >= RIGHTEDGE )		/* check for bounce	*/
			dir = -1;
		if ( pos <= LEFTEDGE )
			dir = +1;
		millisleep(delay);
	}
}
