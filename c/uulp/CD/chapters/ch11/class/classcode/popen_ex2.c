#include	<stdio.h>

/*
 *	popen_ex2.c
 *		shows how to use popen() to read from rwho
 *		to get list of all users on local network
 *		Note: could be useful for an expanded version
 *		of watch.c
 */

main()
{
	FILE	*fp;
	char	b[512];

	fp = popen( "rwho", "r" );
	while( fgets( b, 512, fp ) != NULL )
		fprintf(stdout, "%s", b );
	pclose(fp);
}
