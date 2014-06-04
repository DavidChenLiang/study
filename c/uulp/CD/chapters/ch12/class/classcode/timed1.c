#include	<stdio.h> 
#include	  <time.h>

/*
 * timed1.c
 *	a date-time server that replies with the output of ctime
 */

#define	PORTNUM	9999
#define oops(s) { perror(s); exit(1) ; }

main()
{
	int	sock, fd;

	sock = make_server_socket( PORTNUM );
	if ( sock == -1 ) oops( "make_server_socket" );

	while( ( fd = accept(sock,NULL,NULL) ) != -1 )
	{
		process_request(fd);
		close(fd);
	}
}
process_request(fd)
/*
 * send the date out to the client via fd
 */
{
	time_t	now;
	char	*cp, *ctime();

	time( &now );			/* get time from system	*/
	cp = ctime( &now );		/* convert to string	*/

	if ( write( fd, cp, strlen(cp) ) != strlen(cp) )
		perror("write");
}
