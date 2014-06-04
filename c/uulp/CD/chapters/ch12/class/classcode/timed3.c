#include	<stdio.h>
#include	<time.h>
#include	<signal.h>
#include	<errno.h>

/*
 * timed3.c
 *	a date-time server that replies with the output of ctime
 *	this version uses fork() and exec() and dup2() to get
 *	the date command to generate the time and date and send
 *	it over the fd.
 *
 * 	this one does not wait.  It does call sleep in the child
 *	to allow a demo of zombies
 */

#define	PORTNUM	21500
#define oops(s) { perror(s); exit(1) ; }

extern int errno;

main()
{
	int	sock, fd;
	void	child_waiter();

	signal( SIGCHLD, child_waiter );
	sock = make_server_socket( PORTNUM );
	if ( sock == -1 ) oops( "make_server_socket" );

	while( 1 )
	{
		fd = accept(sock,NULL,NULL );
		if ( fd == -1 ){
			if ( errno == EINTR )
				continue;
			break;
		}
		process_request(fd);
		close(fd);
	}
}
process_request(fd)
/*
 * send the date out to the client via fd
 */
{
	int	pid;

	pid = fork();
	if ( pid == 0 ){		/* child			*/
		dup2( fd, 1 );			/* moves socket to fd 1	*/
		close(fd);			/* closes socket	*/
		execlp("date","date",NULL);	/* exec date		*/
		oops("execlp date");
	}
}

void
child_waiter()
{
	int	pid;

	signal( SIGCHLD, child_waiter );
	while( ( pid = wait(NULL) ) != -1 )
		printf("Just caught %d\n", pid );
}

