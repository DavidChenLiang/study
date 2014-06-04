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
	char   *sockname;

	if ( ac != 2 ){
		fprintf(stderr,"usage: %s socketname\n", av[0] );
		exit(1);
	}
	sockname = av[1];

	/*
	 * make the connection
	 */
	fd = ud_connect_to_server( sockname );
	if ( fd == -1 ) oops( "connecting to server" );
	get_info_from_server( sockname, fd );
	close(fd);
}

/*
 * print a header, then copy data from fd to stdout
 */
get_info_from_server(char *sockname, int fd )
{
	char   message[BUFSIZ];             /* to receive message */
	int    messlen;                     /* for message length */

	printf( "The time report from %s:\n", sockname);
	while ((messlen = read( fd, message, BUFSIZ )) > 0 )
		if ( write( 1, message, messlen ) != messlen )  
			oops( "write" );
	
	if ( messlen == - 1 ) oops( "read" ) ;
	close( fd );    
}
