

#include	<stdio.h>


main()
{
	FILE	*fp, *fdopen();
	int	fd;

	fd = open( "hello", 0 );
	fp = fdopen( fd, "r" );
	
	catthefile( fp );

	fclose( fp );
}

catthefile( fp )
FILE *fp;
/*
 * purpose: copy from stream to stdou
 */
{
	int	c;

	while (  ( c = getc(fp) ) != EOF )
		putchar( c );
}
