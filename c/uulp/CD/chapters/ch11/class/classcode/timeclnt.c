#include       <stdio.h>
#include       <sys/types.h>
#include       <sys/socket.h>
#include       <netinet/in.h>
#include       <netdb.h>

#define        HOSTNAME        "host2"
#define        PORTNUM         8822
#define        oops(msg)       { perror(msg); exit(1); }

main()
{
	struct sockaddr_in  servadd;        /* the number to call */
	struct hostent      *hp;            /* used to get number */
	int    sock_id, sock_fd;            /* the socket and fd  */
        char   message[BUFSIZ];             /* to receive message */
        int    messlen;                     /* for message length */

       /*
        *      build the network address of where we want to call
        */

       hp = gethostbyname( HOSTNAME );
       if ( hp == NULL ) oops("no such computer");

       bzero( &servadd, sizeof( servadd ) );   /* zero the address     */
       servadd.sin_family = AF_INET ;          /* fill in socket type  */
                                               /* and machine address  */
       bcopy( hp->h_addr, &servadd.sin_addr, hp->h_length);
       servadd.sin_port = htons(PORTNUM);      /* host to num short    */

       /*
        *        make the connection
        */

       sock_id = socket( AF_INET, SOCK_STREAM, 0 );    /* get a line   */
       if ( sock_id == -1 ) oops( "socket" );          /* or fail      */
                                                       /* now dial     */
       if ( connect( sock_id, &servadd, sizeof(servadd)) !=0  )  
               oops( "connect" );

       /*
        *      we're connected to that number, read from socket
        */

       messlen = read( sock_id, message, BUFSIZ );     /* read stuff   */
       if ( messlen == - 1 )
               oops( "read" ) ;
       if ( write( 1, message, messlen ) != messlen )  /* and write to */
               oops( "write" );                        /* stdout       */
       close( sock_id );    
}
