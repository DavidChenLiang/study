
#include	<stdio.h>

main()
{
	FILE	*fp;
	char	b[512];

	fp = popen( "mail user1 user2", "w" );
	fprintf( fp, "hello...how are you?\n" );
	pclose( fp );
}
