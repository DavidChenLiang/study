#include	<stdio.h>
#include	<termios.h>

/*
 * password_input.c
 *
 *  purpose:	read in input with *'s in place of chars
 *		need to turn off icanon and echo and put
 *		*'s for each char read.
 *  returns	number of chars read
 *  thanks to:	mrgc (mar 2001)
 */

main()
{
	char	b[100];
	int	n;

	n = get_password(b, 100, '*');
	printf("you typed in \"%s\"\n", b);
}

int
get_password(char buf[], int maxlen, int star)
{
	struct termios ttystate, orig;
	int	c;
	int	pos = 0;		/* buffer position */

	tcgetattr(0, &ttystate);		/* get current settings	*/
	orig = ttystate;			/* store orig settings	*/
	ttystate.c_lflag   &= ~ICANON;		/* no canonical proc.	*/
	ttystate.c_lflag   &= ~ECHO;		/* no echoing please	*/
	ttystate.c_cc[VMIN] = 1;		/* read chars 1-by-1	*/
	tcsetattr(0,TCSANOW, &ttystate);	/* set new ones now	*/

	while( ( c = getchar() ) != '\n' && c != '\r' )
	{
		if ( pos < maxlen-1 ){
			buf[pos++] = c ;
			putchar(star);
		}
	}
	/*
	 * saw end of line here
	 */
	buf[pos] = '\0';
	tcsetattr(0, TCSANOW, &orig );
	return pos;
}

