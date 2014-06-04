#include	<curses.h>

/*
 * hello5.c
 *  bounce a message back and forth across the screen
 */

#define	LEFTEDGE	10
#define	RIGHTEDGE	30
#define	ROW		10

main()
{
	char	msg[] = " Hello ";		/* notice padding spaces */
	int	dir = +1;
	int	pos = LEFTEDGE ;

	initscr();
	clear();

	while(1){
		move(ROW,pos);
		addstr( msg );			/* draw it */
		move(LINES-1,COLS-1);		/* park the cursor	*/
		refresh();
		pos += dir;			/* advance position	*/
		if ( pos >= RIGHTEDGE )		/* check for bounce	*/
			dir = -1;
		if ( pos <= LEFTEDGE )
			dir = +1;
		sleep(1);
	}
}
