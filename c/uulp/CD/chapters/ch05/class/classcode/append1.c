
#include	<stdio.h>
#include	<fcntl.h>

/*
 *   append1.c
 *	purpose: demonstrate how to use O_APPEND to ensure appends
 *	 action: opens a file, then lseeks to end, then waits, then writes
 *        value: run two of these and watch the fun
 *        usage: append1 filename message [delay]
 *        shows: how to set attributes when opening
 */

#define oops(s)  { perror(s); exit(1); }

main(int ac, char *av[])
{
	int	fd, delay = 1;

	if ( ac < 3 ) exit(2);				/* usage	*/
	if ( ac == 4 ) delay = atoi( av[3] );		/* delay arg	*/

	if ( ( fd = open( av[1], O_WRONLY|O_CREAT|O_APPEND, 0644 ) ) == -1 )
		oops( "open" );
	lseek( fd, 0L, 2 );				/* seek to end	*/
	sleep(delay);					/* pause	*/
	if ( write(fd,av[2],strlen(av[2])) == -1 )	/* write	*/
		oops( "write" );
	write( fd, "\n", 1 );				/* add newline	*/
	if ( close(fd) == -1 )
		oops( "close" );
}
