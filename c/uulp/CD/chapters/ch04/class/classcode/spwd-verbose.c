#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>

/**
 **	a simplified version of pwd
 **
 **	starts in current directory and recursively
 **	climbs up to root of filesystem, prints top part
 **	then prints current part
 **
 **	uses readdir() to get info about each thing
 **/

ino_t	get_inode();

int
main()
{
	int	my_inode = get_inode( "." );	/* you are here 	*/
	printpathto( my_inode );		/* print path to here	*/
	putchar('\n');				/* then add newline	*/
	return 0;
}

printpathto( ino_t this_inode )
/*
 *	prints path leading down to an object with this inode
 *	kindof recursive
 */
{
	int	my_inode ;
	char	its_name[BUFSIZ];

	chdir( ".." );					/* up one dir	*/

	inum_to_name( this_inode , its_name );		/* get its name	*/

	my_inode = get_inode( "." );			/* print head	*/
	if ( my_inode != get_inode( ".." ) )		/* of pathname	*/
		printpathto( my_inode );		/* recursively	*/
	printf("/%s", its_name );			/* now print	*/
							/* name of this	*/
}

inum_to_name(ino_t inode_to_find , char *namebuf)
/*
 *	looks through current directory for a file with this inode
 *	number and copies its name into namebuf
 */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */

printf("looking for %d .. \n", inode_to_find );
	dir_ptr = opendir( "." );
	if ( dir_ptr == NULL ){
		fprintf(stderr, "cannot open a directory\n");
		exit(1);
	}

	/*
	 * search directory for a file with specified inum
	 */

	while ( ( direntp = readdir( dir_ptr ) ) != NULL ){
printf("   %6d %s\n", direntp->d_ino, direntp->d_name );
		if ( direntp->d_ino == inode_to_find )
		{
			strcpy( namebuf, direntp->d_name );
			closedir( dir_ptr );
			return 0;
		}
	}
	fprintf(stderr, "error looking for inum %d\n", inode_to_find);
	exit(1);
}

ino_t
get_inode( char *fname )
/*
 *	returns inode number of the file
 */
{
	struct stat info;

	if ( stat( fname , &info ) == -1 ){
		fprintf(stderr, "Cannot stat ");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}
