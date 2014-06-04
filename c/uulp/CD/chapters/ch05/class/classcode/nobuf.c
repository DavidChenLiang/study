#include	<stdio.h>
#include	<fcntl.h>
#include	<unistd.h>

/*
 *   nobuff.c
 *	purpose: demonstrate use of fcntl to set a fd attribute
 *	 action: opens a file, then uses fcntl to change attrib
 *               then writes some data
 *        value: see how fcntl works
 */

#define oops(s)  { perror(s); exit(1); }
#define	DATALEN	10000

char	buf[DATALEN] ;

main()
{
	int	fd, attribs;

	if ( ( fd = open( "junkfile", O_WRONLY|O_CREAT, 0644 ) ) == -1 )
		oops( "open" );
	attribs = fcntl( fd, F_GETFL );			/* get attribs	*/
	attribs |= O_SYNC ;				/* turn on SYNC */
	if ( fcntl(fd,F_SETFL,attribs) == -1 )		/* set attribs	*/
		oops( "fcntl" );
	if ( write( fd, buf, DATALEN ) == -1 )
		oops( "write" );
	if ( close( fd ) == -1 )
		oops( "close" );
}
