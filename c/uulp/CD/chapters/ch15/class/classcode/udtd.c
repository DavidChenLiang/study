#include       <stdio.h>
#include       <sys/types.h>
#include       <sys/socket.h>
#include       <sys/un.h>

/*
 * the time server using Unix Domain Sockets
 */

#define	 SOCK_NAME	"/tmp/timesock"

main()
{
        struct  sockaddr_un   saddr;   /* build our address here */
	int	sock_id, sock_fd;

       /* get a AF_UNIX socket */

       sock_id = socket( AF_UNIX, SOCK_STREAM, 0 );   
       if ( sock_id == -1 ) return -1;

       /* build the address for a AF_UNIX socket */
       /* then bind that address to the socket   */

       saddr.sun_family = AF_UNIX ;            /* fill in socket type  */
       strcpy(saddr.sun_path, SOCK_NAME);      /* fill in socket name  */

       if ( bind(sock_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0 )
                return -1;

       /*  listen as we did with AF_INET 	*/
       if ( listen(sock_id, 1) != 0 ) return -1;

       /* same old main loop */
	
       while( ( sock_fd = accept( sock_id, NULL, NULL ) ) != -1 ){
		handle_call( sock_fd );
		close( sock_fd );
	}
	unlink( SOCK_NAME );
}

#include	  <time.h>

handle_call( int fd )
{
	time_t	now;
	char	*cp, *ctime();

	time( &now );			/* get time from system	*/
	cp = ctime( &now );		/* convert to string	*/

	if ( write( fd, cp, strlen(cp) ) != strlen(cp) )
		perror("write");
}
