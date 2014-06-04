
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>

#define	PORTNUM	8823
#define	oops(msg)	{ perror(msg) ; exit(1) ; }


void main(ac, av)
char **av;
{

	struct	sockaddr_in	saddr;	/* a struct to hold a socket address */
	struct	hostent		*hp;
	char	hostname[256];		/* get hostname here	*/
	int	slen, sock_id, sock_fd, ch;
	FILE	*sock_fp, *cmdfp;
	char	cmd[BUFSIZ];		/* command to execute */
	int	cmdlen;

	/*
	 *	step 1: build our network address
 	 *		 domain is internet, hostname is local host,
	 *		 port is some arbitrary number
	 */

	gethostname( hostname );		/* where am I ?		*/
	hp = gethostbyname( hostname );		/* get info about host	*/

	bzero( &saddr, sizeof(saddr) );		/* zero struct		*/
						/* fill in hostaddr	*/
	bcopy( hp->h_addr, &saddr.sin_addr, hp->h_length);
	saddr.sin_family = AF_INET ;		/* fill in socket type	*/
	saddr.sin_port = htons(PORTNUM);	/* fill in socket port	*/

	/*
	 *	step 2: ask kernel for a socket, then bind address
	 */

	sock_id = socket( AF_INET, SOCK_STREAM, 0 );	/* get a socket	*/
	if ( sock_id == -1 ) oops( "socket" );
	if ( bind(sock_id, &saddr, sizeof(saddr)) != 0 )/* bind it to	*/
		oops( "bind" );				/* an address	*/

	/*
	 *	step 3: tell kernel we want to listen for calls
	 */

	if ( listen(sock_id, 1) != 0 ) oops( "listen" );
	while ( 1 ){
		sock_fd = accept(sock_id, NULL, NULL); /* wait for call */
		if ( sock_fd == -1 )
			oops( "accept" );	/* error getting calls	*/

		cmdlen = read( sock_fd, cmd, BUFSIZ );
		if ( strncmp( cmd, "quit", 4 ) == 0 )
			exit(0);
		if ( cmdlen == -1 ) oops( "read" );
		cmd[cmdlen] = '\0';

		sock_fp = fdopen(sock_fd,"w");	/* we'll write to the	*/
		if ( sock_fp == NULL )		/* socket as a stream	*/
			oops( "fdopen" );	/* unless we can't	*/

		cmdfp = popen( cmd, "r" );	/* and read from the	*/
		if ( cmdfp == NULL )		/* command		*/
			fputs( "didnt work\n", sock_fp);
		else {
			while ( (ch = getc( cmdfp )) != EOF )
				putc(ch, sock_fp );
			pclose( cmdfp );
		}
		fclose( sock_fp );		/* release connection	*/
	}
}
