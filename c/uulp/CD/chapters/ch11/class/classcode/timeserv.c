#include  <stdio.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <netdb.h>

#define   PORTNUM  8822       /* our time service phone number */
#define   oops(msg)      { perror(msg) ; exit(1) ; }


void main(ac, av)
char **av;
{
        struct  sockaddr_in   saddr;   /* build our address here */
	struct	hostent		*hp;   /* this is part of our    */
	char	hostname[256];         /* address 	         */
	int	slen,sock_id,sock_fd;  /* line id, file desc     */
	FILE	*sock_fp;              /* use socket as stream   */
        char    *ctime();              /* convert secs to string */
        long    time(), thetime;       /* time and the val       */ 


       /*
        *      step 1: build our network address
        *               domain is internet, hostname is local host,
        *               port is some arbitrary number
        */

       gethostname( hostname );                /* where am I ?         */
       hp = gethostbyname( hostname );         /* get info about host  */

       bzero( &saddr, sizeof(saddr) );         /* zero struct          */
                                               /* fill in hostaddr     */
       bcopy( hp->h_addr, &saddr.sin_addr, hp->h_length);
       saddr.sin_family = AF_INET ;            /* fill in socket type  */
       saddr.sin_port = htons(PORTNUM);        /* fill in socket port  */

       /*
        *      step 2: ask kernel for a socket, then bind address
        */

       sock_id = socket( AF_INET, SOCK_STREAM, 0 );    /* get a socket */
       if ( sock_id == -1 ) oops( "socket" );

       if ( bind(sock_id, &saddr, sizeof(saddr)) != 0 )/* bind it to   */
               oops( "bind" );                         /* an address   */

       /*
        *      step 3: tell kernel we want to listen for calls
        */

       if ( listen(sock_id, 1) != 0 ) oops( "listen" );

       while ( 1 ){
               sock_fd = accept(sock_id, NULL, NULL); /* wait for call */
		printf("Wow! got a call!\n");
               if ( sock_fd == -1 )
                       oops( "accept" );       /* error getting calls  */

               sock_fp = fdopen(sock_fd,"w");  /* we'll write to the   */
               if ( sock_fp == NULL )          /* socket as a stream   */
                       oops( "fdopen" );       /* unless we can't      */

               thetime = time(NULL);           /* get time             */
                                               /* and convert to strng */
               fprintf( sock_fp, "The time is...");
               fprintf( sock_fp, "%s", ctime(&thetime) ); 
	       fprintf( sock_fp, "the temperature is crummy\n");
               fclose( sock_fp );              /* release connection   */
       }
}
