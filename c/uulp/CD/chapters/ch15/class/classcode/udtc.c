#include       <stdio.h>
#include       <sys/types.h>
#include       <sys/socket.h>
#include       <sys/un.h>

#define	SOCK_NAME	"/tmp/timesock"

main( )
{
	struct sockaddr_un  servadd;        /* the number to call */
	int    sock_id;                     /* the socket and fd  */
	char   buf[BUFSIZ];
	int    n;

	/* get a socket to call from */

       sock_id = socket( AF_UNIX, SOCK_STREAM, 0 );    /* get a line   */
       if ( sock_id == -1 ) return -1;          	/* or fail      */

	/* build the address of the server */

       servadd.sun_family = AF_UNIX ;          /* fill in socket type  */
       strcpy(servadd.sun_path, SOCK_NAME);    /* the name             */

	/* make the connection		*/

       if( connect(sock_id,(struct sockaddr *)&servadd,sizeof(servadd)) !=0 )
               return -1;

	while( ( n = read( sock_id, buf, BUFSIZ) ) > 0 )
		write(1, buf, n );
}
