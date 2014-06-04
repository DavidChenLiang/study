#include	<stdio.h>
#include	<fcntl.h>

/*
 *	open a file for O_CREAT and O_RDWR
 *	then write some stuff and read it back
 */

main()
{
	int	fd, charsread;
	char	buf[100];

	fd = open( "demo", O_CREAT|O_RDWR , 0644 );
	write( fd, "hello", 5 );
	lseek( fd, -1L, 2 );		/* skip first char */
	charsread = read(fd , buf, 1 );
	write( 1, buf, charsread );
	close( fd );
}
