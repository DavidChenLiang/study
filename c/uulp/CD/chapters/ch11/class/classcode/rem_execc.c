#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>

#define		HOSTNAME	"host2"
#define		PORTNUM		8823
#define		oops(msg)	{ perror(msg); exit(1); }

main()
{

	struct sockaddr_in rxa;
	struct hostent 	  *hp;
	FILE	*sock_fp;
	int	sock_id, sock_fd, ch;
	char	cmd[BUFSIZ];

	/*
	 *	build the network address of where we want to call
	 */

	hp = gethostbyname( HOSTNAME );
	if ( hp == NULL ) oops("no such computer");

	bzero( &rxa, sizeof( rxa ) );		/* zero the address	*/
	rxa.sin_family = AF_INET ;		/* fill in socket type	*/
						/* and machine address	*/
	bcopy( hp->h_addr, &rxa.sin_addr, hp->h_length);
	rxa.sin_port = htons(PORTNUM);		/* format number	*/

	/*
	 *	make the connection
	 */

	sock_id = socket( AF_INET, SOCK_STREAM, 0 );	/* get a line	*/
	if ( sock_id == -1 ) oops( "socket" );		/* or fail	*/
	if ( connect( sock_id, &rxa, sizeof(rxa))!=0 )	/* dial number	*/
		oops( "connect" );

	/*
	 *	we're connected to that number,
	 *	open socket as a readable stream and copy to stdout
	 */

	gets( cmd );
	if ( write( sock_id, cmd, strlen(cmd) ) == -1 )
		oops( "write" );		
	sock_fp = fdopen( sock_id , "r" );		/* open to read	*/
	if ( sock_fp == NULL )
		oops( "fdopen" ) ;
	while ( (ch = getc(sock_fp)) != EOF )		/* copy from	*/
		putchar( ch );				/* stream	*/
	fclose( sock_fp );
}
