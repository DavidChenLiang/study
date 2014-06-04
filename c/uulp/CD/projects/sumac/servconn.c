#include	<stdio.h>

/*
 * servconn.c
 *	server conection functions
 *	The pop client needs to set up a connection to a pop server
 *	then it needs to say things to the server and it needs to
 *	receive replies and data back from the server.
 *
 *  this file encapulates that stuff.  It needs a little bit of work
 *  but is is mostly ok.
 *
 * 	The functions are:
 *	   SCconnect(host)      - connect to server
 *				   (returns -1 on error)
 *         SCtell_server( str ) - send a string to the server
 *				   (returns -1 on error)
 *         SCgetstr( buf, len ) - reads one line from server (like fgets)
 *				   (returns -1 on error)
 *
 *  this `object' consists of one connection.  It might be nicer to
 *  have SCconnect return a connection id so that a client could have
 *  connections open to several servers at once.  Not for now, though.
 */

#define	POP_PORT	110
#define	MAXMSG		512	/* message length max length	*/

static int	pop_fd = -1;	/* write to this fd for output	*/
static FILE	*infp = NULL;	/* read from this fd for input	*/

/* #define	CRLF_NEEDED	/* not needed for body		*/

int	make_server_socket();
int	connect_to_server();

SCconnect(char *host)
{
	char	buf[512];

	/* connect to server */
	if ( (pop_fd = connect_to_server( host, POP_PORT )) == -1 )
		return -1;

	/* buffer reading part */
	if ( (infp = fdopen( pop_fd, "r" )) == NULL )
		return -1;

	return 0;
}


SCtell_server(char *str)
/*
 * purpose: send a mesage to the server
 *     arg: str is a string
 *     ret: -1 for error, 0 for ok
 *   notes: this appends CRLF to the string and sends it
 */
{
	char	buf[MAXMSG+1];
	int	len = strlen(str);
	
	if ( pop_fd == -1  )
		return -1;
	if ( len + 3 > MAXMSG )
		return -1;
	sprintf(buf, "%s\r\n", str );
	if ( write( pop_fd, buf, len+2 ) != len+2 )
		return -1;
	return 0;
}

SCgetstr( char *buf, int len )
/*
 * purpose: retrieve one line from server
 *    args: a place to store reply, length of buffer
 * returns: -1 on error (including EOF), 0 if ok
 *   notes: the rfc says reply is <= 512 bytes
 *	    this makes sure the reply ends with CRLF
 * 	    AND removes the CRLF from the line
 *  extra!: this one undoes byte-stuffing (read the RFC)
 */
{
	char	*rv = NULL;

	if ( pop_fd == -1  )
		return -1;

	if( fgets(buf,len,infp) == NULL )		/* EOF ? */
		return -1;
#ifdef	CRLF_NEEDED
	if ( strcmp(buf+strlen(buf)-2, "\r\n") != 0 )	/* ends with CRLF? */
		return -1;
#endif

	if ( *buf == '.' && strlen(buf) > 3 ){		/* byte-stuffed? */
		char *s = buf+1, *d = buf;
		while(*d++ = *s++) ;
	}
	buf[strlen(buf)-2] = '\0';
	return 0;
}
