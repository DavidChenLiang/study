#include	<stdio.h>
#include	<stdlib.h>

/*
 * popendemo.c
 *	demonstrates how to open a program for standard i/o
 *	important points:
 *		1. popen() returns a FILE *, just like fopen()
 *		2. the FILE * it returns can be read/written
 *		   with all the standard functions
 *		3. you need to use pclose() when done
 */
int
main()
{
	FILE	*fp;
	char	buf[100];
	int	i = 0;

	fp = popen( "who", "r" );

	while ( fgets( buf, 100, fp ) != NULL )
		printf("%3d %s", i++, buf );

	pclose( fp );
	return 0;
}
