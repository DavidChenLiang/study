#include	<stdio.h>

/**
 **	stdin copy
 **			uses standard file i/o library
 **/

main( ac, av )
char **av;
{
	FILE	*in_fp, *out_fp, *fopen();
	int	c;
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
	if ( ( in_fp=fopen(av[1], "r") ) == NULL )
		oops("Cannot open ", av[1]);

	if ( ( out_fp=fopen( av[2], "w" ) ) == NULL )
		oops( "Cannot rewrute", av[2]);
						/*
						 *	copy files
						 */
	while ( ( c=getc(in_fp) ) != EOF )
		if ( putc( c, out_fp) == EOF )
			oops("Write error to ", av[2]);
						/*
						 *	close them up
						 */
	if ( fclose(in_fp) == EOF || fclose(out_fp) == EOF )
		oops("Error closing files","");
}

oops(s1, s2)
char *s1, *s2;
{
	fprintf(stderr,"Error: %s%s\n", s1, s2);
	exit(1);
}
