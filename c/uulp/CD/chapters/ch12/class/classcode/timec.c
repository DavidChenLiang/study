#include       <stdio.h>

/*
 * timec.c
 *
 *	connects to time server and prints out report
 *	args: hostname portnum
 *	action: connect to server, read and print one line
 */

#define        oops(msg)       { perror(msg); exit(1); }

main(int ac, char *av[])
{
	int    fd;			    /* the connected socket	*/
	char   *hostname;

	if ( ac != 3 ){
		fprintf(stderr,"usage: %s hostname portnum\n", av[0] );
		exit(1);
	}
	hostname = av[1];

	/*
	 * make the connection
	 */
	fd = connect_to_server( hostname, atoi(av[2]) );
	if ( fd == -1 ) oops( "connecting to server" );
	talk_with_server( fd );
	close(fd);
}

/*
 * print a header, then copy data from fd to stdout
 */
talk_with_server( int fd )
{
	char   buf[BUFSIZ];             /* to receive message */
	int    messlen;                 /* for message length */

	printf( "The time report from the server: ");
	fflush(stdout);
	while ((messlen = read( fd, buf, BUFSIZ )) > 0 )
		if ( write( 1, buf, messlen ) != messlen )  
			oops( "write" );
	
	if ( messlen == - 1 ) oops( "read" ) ;
}
