#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>

main(int ac, char *av[])
{
	while( --ac )
		info( *++av );
}

info( char *s )
{
	struct stat stb;

	if ( stat( s, &stb ) != -1 )
		printf("%s\t%d\t%x", s, stb.st_ino, (int) stb.st_dev);
	putchar('\n');
}
