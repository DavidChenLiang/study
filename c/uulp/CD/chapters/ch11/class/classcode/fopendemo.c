#include	<stdio.h>

/* fopendemo.c
 *	purpose: a simple review of how fopen works
 *	Notes:	 fopen() returns a FILE *
 *		 fgets(), getc(), fscanf() can be used
 *		 need fclose() when done
 */

main()
{
	FILE	*fp;
	char	b[512];

	fp = fopen( "/etc/passwd", "r" );
	while( fgets( b, 512, fp ) != NULL )
		fprintf(stdout, "%s", b );
	fclose(fp);
}
