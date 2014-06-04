#include	<stdio.h>
#include	<sys/syslimits.h>

/**
 **	mv2 version 1
 **
 **		if last arg is a dir, then move all files into there
 **		if two args and last is a file, then move first to
 **		second.  will clobber second if exists.
 **		Uses isadir .
 **
 **		problems: 1) what if an arg is a dir?
 **			  2) what about paths in source files?
 **/

main( int ac, char *av[] )
{
	if ( ac < 3 ){
		fprintf( stderr, "too few args\n");
		exit(1);
	}

	/*
	 *	if last arg is a dir, then move args to there
 	 */
	if ( isadir( av[ac-1] ) )
		mv_to_newdir(ac-1,av,av[ac-1]);

	/*
	 *	last arg is not a dir, so must be two args only
	 */
	else if ( ac != 3 ){
		fprintf( stderr, "too many args\n");
		exit(1);
	}
	else mv(av[1], av[2]);
}

mv_to_newdir( int ac, char *av[], char *newdir )
/*
 *	move av[1], av[2], ... av[ac-1] into newdir
 */
{
	char	newpath[PATH_MAX];
	int	pos ;

	for( pos = 1 ; pos<ac; pos++ ){
		sprintf( newpath , "%s/%s", newdir, av[pos]);
		mv( av[pos] , newpath );
	}
}

mv( oldname, newname )
char *oldname, *newname;
{
	if ( link(oldname, newname) == -1 || unlink(oldname) == -1 ){
		fprintf(stderr,"error mv'ing %s to %s\n", oldname, newname);
		exit(1);
	}
}
