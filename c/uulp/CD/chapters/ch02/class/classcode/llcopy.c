#include	<stdio.h>
#include	<fcntl.h>

/**
 **	low level copy	
 **			uses read and write with tunable buffer size
 **
 **	usage: llcopy src dest
 **/

#define	BUFFERSIZE	4096
#define	COPYMODE	0644

main( int ac, char *av[] )
{
	int	in_fd, out_fd, n_chars;
	char	buf[BUFFERSIZE];
						/*
						 *	check args
						 */
	if ( ac != 3 ){
		fprintf( stderr, "usage: %s source destination\n", *av);
		exit(1);
	}
						/*
						 *	open files
						 */
	if ( ( in_fd=open(av[1], O_RDONLY) ) == -1 )
		oops("Cannot open ", av[1]);

	if ( ( out_fd=creat( av[2], COPYMODE ) ) == -1 )
		oops( "Cannot creat", av[2]);
						/*
						 *	copy files
						 */
	while ( (n_chars = read( in_fd , buf, BUFFERSIZE )) > 0 )
		if ( write( out_fd, buf, n_chars ) != n_chars )
			oops("Write error to ", av[2]);
						/*
						 *	close them up
						 */
	if ( close(in_fd) == -1 || close(out_fd) == -1 )
		oops("Error closing files","");
}

oops(s1, s2)
char *s1, *s2;
{
	fprintf(stderr,"Error: %s%s\n", s1, s2);
	exit(1);
}
