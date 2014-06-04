#include	<stdio.h>
#include	<termios.h>

/*
 * crmode_demo.c
 *
 *  purpose:	demonstrate how to set, unset, and use char-by-char mode
 *   action:	turns off canonical processing,
 *		turns off echo
 *		sets minimum chars that it needs to get to 1
 *		reads chars and reports them until it sees a 'Q'
 *		resets tty driver, exits
 */

main()
{
	struct termios ttystate, orig;
	int	c;

	tcgetattr(0, &ttystate);		/* get current settings	*/
	orig = ttystate;			/* store orig settings	*/
	ttystate.c_lflag   &= ~ICANON;		/* no canonical proc.	*/
	/* ttystate.c_lflag   &= ~ECHO;		/* no echoing please	*/
	ttystate.c_cc[VMIN] = 1;		/* read chars 1-by-1	*/
	tcsetattr(0,TCSANOW, &ttystate);	/* set new ones now	*/

	while( ( c = getchar() ) != EOF && c != 'Q' )
		printf("Just got %c\n", c );

	tcsetattr(0, TCSANOW, &orig);
}
