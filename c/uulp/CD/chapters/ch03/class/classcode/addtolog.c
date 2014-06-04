#include	<stdio.h>
#include	<fcntl.h>

/*
 * appendtolog
 *
 *	this program adds a line to a logfile at regular intervals
 *	and shows why O_APPEND is needed
 *      usage: addtolog interval name
 */

main(int ac, char *av[])
{
	int	fd;
	int	recordnum = 1;
	int	delay ;
	char	*title ;
	char	buffer[20];

	if ( ac != 3 )
	{
		fprintf(stderr, "usage: %s interval title\n", av[0] );
		exit(1);
	}
	delay = atoi(av[1]);
	title  = av[2];
	fd = open( "logfile", O_WRONLY|O_CREAT, 0755 );
	if ( fd == -1 ){
		perror( "logfile" ); exit(1);
	}
	lseek( fd, 0L, 2 );

	while(1)
	{
		sprintf( buffer, "%9s%10d\n", title , recordnum++ );
		write( fd, buffer, 20 );
		sleep(delay);
	}
}
