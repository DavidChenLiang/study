#include	<stdio.h>
#include	<fcntl.h>

/*
 * noblock_demo.c	95.03.10
 *
 * purpose: demonstrate how non-blocking (i.e. no-delay) input works
 *	    shows how to set a file descriptor to operate in non-delay mode
 *	    shows how to take a file out of non-delay mode
 */

main()
{
	int	flags, c;
	flags = fcntl(0, F_GETFL, 0);		/* stdin is file desc 0	*/
	flags |= O_NDELAY ;			/* set no delay bit	*/
	fcntl(0, F_SETFL, flags);		/* install new setting	*/

	if ( ( c = getchar() ) == EOF )		/* getchar will return	*/
		printf("No input!");		/* no chars right now	*/
	flags &= ~O_NDELAY;			/* turn off bit		*/
	fcntl(0, F_SETFL, flags );		/* store them		*/
}
