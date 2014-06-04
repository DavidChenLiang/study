#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>

/*
 *	stat1.c		a user interface to the stat system call
 *			for each arg, it lists all interesting
 *			file info.  Has a lot of numbers, though..
 */
main( int ac, char *av[] )
{
	while ( --ac )
		dostat( *++av );
}
dostat( char *filename )
{
	struct stat info;

	printf("%s:\n", filename );			/* print name	 */
	if ( stat(filename, &info) == -1 )		/* cannot stat	 */
		perror( filename );			/* say why	 */
	else					/* else show info	 */
	{
		printf("\t  mode: %o\n", (int) info.st_mode);	/* mode	 */
		printf("\t links: %d\n", (int) info.st_nlink);	/* links */
		printf("\t owner: %d\n", (int) info.st_uid);	/* owner */
		printf("\t group: %d\n", (int) info.st_gid);	/* group */
		printf("\t  size: %ld\n",(long)info.st_size);	/* size  */
		printf("\t   mod: %ld\n",(long)info.st_mtime);	/* mod   */
		printf("\taccess: %ld\n",(long)info.st_atime);	/* access*/
	}
}

