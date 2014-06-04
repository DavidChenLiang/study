#include       <stdio.h>
#include       <sys/types.h>
#include       <sys/socket.h>
#include       <netinet/in.h>
#include       <netdb.h>
#include       <sys/un.h>

/*
 *	socklib2.c - contains unix domain versions of these functions
 *
 *	This file contains functions used lots when writing internet
 *	client/server programs.  The two main functions here are:
 *
 *	make_server_socket( portnum )	returns a server socket
 *					or -1 if error
 *
 *	connect_to_server(char *hostname, int portnum)
 *					returns a connected socket
 *					or -1 if error
 */ 

int
make_server_socket( int portnum )
{
        struct  sockaddr_in   saddr;   /* build our address here */
	struct	hostent		*hp;   /* this is part of our    */
	char	hostname[256];         /* address 	         */
	int	sock_id;	       /* line id, file desc     */

       /*
        *      step 1: build our network address
        *               domain is internet, hostname is local host,
        *               port is some arbitrary number
        */

       gethostname( hostname , 256 );          /* where am I ?         */
       hp = gethostbyname( hostname );         /* get info about host  */
       if ( hp == NULL )
		return -1;

       bzero( &saddr, sizeof(saddr) );         /* zero struct          */
                                               /* fill in hostaddr     */
       bcopy( hp->h_addr, &saddr.sin_addr, hp->h_length);
       saddr.sin_family = AF_INET ;            /* fill in socket type  */
       saddr.sin_port = htons(portnum);        /* fill in socket port  */

       /*
        *      step 2: ask kernel for a socket, then bind address
        */

       sock_id = socket( AF_INET, SOCK_STREAM, 0 );    /* get a socket */
       if ( sock_id == -1 ) return -1;
						       /* give it      */
       if ( bind(sock_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0 )
                return -1;				/* an address	*/

       /*
        *      step 3: tell kernel we want to listen for calls
        */

       if ( listen(sock_id, 1) != 0 ) return -1;

	return sock_id;
}

int
connect_to_server( char *hostname, int portnum )
{
	struct sockaddr_in  servadd;        /* the number to call */
	struct hostent      *hp;            /* used to get number */
	int    sock_id, sock_fd;            /* the socket and fd  */
        char   message[BUFSIZ];             /* to receive message */
        int    messlen;                     /* for message length */

       /*
        *      build the network address of where we want to call
        */

       hp = gethostbyname( hostname );
       if ( hp == NULL ) return -1;

       bzero( &servadd, sizeof( servadd ) );   /* zero the address     */
       servadd.sin_family = AF_INET ;          /* fill in socket type  */
                                               /* and machine address  */
       bcopy( hp->h_addr, &servadd.sin_addr, hp->h_length);
       servadd.sin_port = htons(portnum);      /* host to num short    */

       /*
        *        make the connection
        */

       sock_id = socket( AF_INET, SOCK_STREAM, 0 );    /* get a line   */
       if ( sock_id == -1 ) return -1;          	/* or fail      */
                                                       /* now dial     */
       if( connect(sock_id,(struct sockaddr *)&servadd,sizeof(servadd)) !=0 )
               return -1;

       /*
        *      we're connected to that number, return the socket
        */

	return sock_id ;
}

/*
 * make a server socket in the Unix domain, i.e. a named socket
 */

int
ud_make_server_socket( char *pathname )
{
        struct  sockaddr_un   saddr;   /* build our address here */
	int	sock_id;	       /* line id, file desc     */

       /*
        *      step 1: build the socket address structure
        *               it has three parts: family, length, path
        */

       bzero( &saddr, sizeof(saddr) );         /* zero struct          */
       saddr.sun_family = AF_UNIX ;            /* fill in socket type  */
       strcpy(saddr.sun_path, pathname);       /* fill in socket name  */
       /* saddr.sun_len = 1 + strlen(pathname);   /* includes nul         */

       /*
        *      step 2: ask kernel for a socket, then bind address
        */

       sock_id = socket( AF_UNIX, SOCK_STREAM, 0 );    /* get a socket */
       if ( sock_id == -1 ) return -1;
						       /* give it      */
       if ( bind(sock_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0 )
                return -1;				/* an address	*/

       /*
        *      step 3: tell kernel we want to listen for calls
        */

       if ( listen(sock_id, 1) != 0 ) return -1;

	return sock_id;
}

int
ud_connect_to_server( char *pathname )
{
	struct sockaddr_un  servadd;        /* the number to call */
	int    sock_id;                     /* the socket and fd  */

       /*
        *      build the network address of where we want to call
        */

       bzero( &servadd, sizeof( servadd ) );   /* zero the address     */
       servadd.sun_family = AF_UNIX ;          /* fill in socket type  */
       strcpy(servadd.sun_path, pathname);     /* the name             */
       /* servadd.sun_len = 1 + strlen(pathname); /* and the length       */

       /*
        *        make the connection
        */

       sock_id = socket( AF_UNIX, SOCK_STREAM, 0 );    /* get a line   */
       if ( sock_id == -1 ) return -1;          	/* or fail      */
                                                       /* now dial     */
       if( connect(sock_id,(struct sockaddr *)&servadd,sizeof(servadd)) !=0 )
               return -1;

       /*
        *      we're connected to that number, return the socket
        */

	return sock_id ;
}
