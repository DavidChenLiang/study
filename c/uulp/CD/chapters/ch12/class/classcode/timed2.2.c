#include	<stdio.h>
#include	<time.h>

/*
 * timed2.c
 *	a date-time server that replies with the output of ctime
 *	this version uses fork() and exec() and dup2() to get
 *	the date command to generate the time and date and send
 *	it over the fd.
 */

#define	PORTNUM	9998
#define oops(s) { perror(s); exit(1) ; }

main()
{
	int	sock, fd;

	sock = make_server_socket( PORTNUM );
	if ( sock == -1 ) oops( "make_server_socket" );

	while( ( fd = accept(sock,NULL,NULL) ) != -1 )
	{
		process_request(fd);
		close(fd);
	}
}
process_request(fd)
/*
 * send the date out to the client via fd
 */
{
	int	pid = fork();

	if ( pid == -1 ) return ;       /* error getting a new process  */
	if ( pid != 0 )  return;	/* parent does not wati		*/


	/* child code here */
	dup2( fd, 1 );			/* moves socket to fd 1	*/
	close(fd);			/* closes socket	*/
	execlp("date","date",NULL);	/* exec date		*/
	oops("execlp date");
}
