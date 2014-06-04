#include	<stdio.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>

/**
 **	ls version 2.0
 **		purpose  list contents of directory or directories
 **		action   if no args, use .  else list files in args
 **		this one uses the cool stuff in stat2.c to
 **		produce nice output
 **/

main(int ac, char *av[])
{
	if ( ac == 1 )
		do_ls( "." );
	else
		while ( --ac ){
			printf("%s:\n", *++av );
			do_ls( *av );
		}
}

do_ls( char dirname[] )
/*
 *	list files in directory called dirname
 */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */

	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
		fprintf(stderr,"ls1: cannot open %s\n", dirname);
	else
	{
		while ( ( direntp = readdir( dir_ptr ) ) != NULL )
			dostat( direntp->d_name );
		closedir(dir_ptr);
	}
}

dostat( filename )
char *filename;
{
	struct stat info;

	if ( stat(filename, &info) == -1 )		/* cannot stat	 */
		perror( filename );			/* say why	 */
	else					/* else show info	 */
		show_file_info( filename, &info );
}

show_file_info( char *filename, struct stat *info_p )
/*
 * display the info about 'filename'.  The info is stored in struct at *info_p
 */
{
	char	*uid_to_name(), *ctime(), *gid_to_name(), *filemode();

	printf( "%s"    , filemode(info_p->st_mode) );
	printf( "%4d "  , (int) info_p->st_nlink);	
	printf( "%-8s " , uid_to_name(info_p->st_uid) );
	printf( "%-8s " , gid_to_name(info_p->st_gid) );
	printf( "%8ld " , (long)info_p->st_size);
	printf( "%.12s ", 4+ctime(&info_p->st_mtime));
	printf( "%s\n"  , filename );

}

/*
 * utility functions
 */

char *
filemode( mode )
/*
 *	returns string of mode info
 *	default to ------- and then turn on bits
 */
{
	static	char	bits[11];
	char	type;

	strcpy( bits, "----------" );

	switch ( mode & S_IFMT ){			/* mask for type */
		case S_IFREG:	type = '-';	break;	/* stays a dash	 */
		case S_IFDIR: 	type = 'd';	break;	/* put a d there */
		case S_IFCHR:	type = 'c';	break;	/* char i/o dev	 */
		case S_IFBLK:	type = 'b';	break;	/* blk. i/o dev	 */
		default:	type = '?';	break;	/* fifo, socket..*/
	}
	bits[0] = type ;

	/* do SUID, SGID, and SVTX later */

	permbits( mode>>6 , bits+1 );			/* owner	*/
	permbits( mode>>3 , bits+4 );			/* group	*/
	permbits( mode    , bits+7 );			/* world	*/

	return bits;
}

permbits( permval, string )
char *string;
/*
 *	convert bits in permval into chars rw and x
 */
{
	if ( permval & 4 )
		string[0] = 'r';
	if ( permval & 2 )
		string[1] = 'w';
	if ( permval & 1 )
		string[2] = 'x';
} 
#include	<pwd.h>

char  *
uid_to_name( uid )
short uid;
/* 
 *	returns pointer to logname associated with uid, uses getpw()
 */	
{
	struct	passwd *getpwuid(), *pw_ptr;

	if ( ( pw_ptr = getpwuid( uid ) ) == NULL )
		return "Unknown" ;
	else
		return pw_ptr->pw_name ;
}

#include	<grp.h>

char *
gid_to_name( gid )
short gid;
/*
 *	returns pointer to group number gid. used getgrgid(3)
 */
{
	struct group *getgrgid(), *grp_ptr;

	if ( ( grp_ptr = getgrgid(gid) ) == NULL )
		return "Unknown" ;
	else
		return grp_ptr->gr_name;
}
