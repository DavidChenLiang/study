#include	<stdio.h>

main()
{
	FILE	*fp;
	char	b[512];

	fp = popen( "who", "r" );
	while( fgets( b, 512, fp ) != NULL )
		fprintf(stdout, "%s", b );
	pclose(fp);
}
