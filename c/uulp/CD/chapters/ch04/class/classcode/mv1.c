#include	<stdio.h>
#include	<errno.h>

/*
 * program  mv1.c
 * purpose  show how to use link and unlink to rename a file
 * notes    checks errno to make it more adaptable
 * note     This version could be replaced by rename() but it
 *          works differently when the target exists
 */

main(int ac, char *av[])
{
	extern int errno ;

	if ( link( av[1], av[2]) != -1 )
		unlink( av[1] );

	else if ( errno == EEXIST )		/* name2 already in use */
	{
		if (unlink( av[2] ) == -1 )	/* not any more		*/
		{
			perror(av[2]);		
			exit(1);
		}
		main(ac,av);
	}
}
