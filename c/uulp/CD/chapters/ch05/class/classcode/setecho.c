#include	<stdio.h>
#include	<termios.h>

/*
 * setecho.c
 *   usage:  setecho [y|n]
 *   shows:  how to read, change, reset tty attributes
 */

main(int ac, char *av[])
{
	struct termios info;

	if ( ac == 1 ) exit(0);

	tcgetattr( 0, &info );			/* get attribs 		*/
	if ( av[1][0] == 'y' )
		info.c_lflag |= ECHO ;		/* turn on bit		*/
	else
		info.c_lflag &= ~ECHO ;		/* turn off bit		*/

	tcsetattr( 0, TCSANOW, &info ); 	/* set attribs		*/
}
