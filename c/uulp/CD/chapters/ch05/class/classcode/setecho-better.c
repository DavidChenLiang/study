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

	if ( tcgetattr( 0, &info ) == -1 ){
		perror("getting attribs");
		exit(1);
	}
	if ( av[1][0] == 'y' )
		info.c_lflag |= ECHO ;		/* turn on bit		*/
	else
		info.c_lflag &= ~ECHO ;		/* turn off bit		*/

	if ( tcsetattr( 0, TCSANOW, &info ) == -1 ){
		perror("Setting attribs");
		exit(1);
	}
}
