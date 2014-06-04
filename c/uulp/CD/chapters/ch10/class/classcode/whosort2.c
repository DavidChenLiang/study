#include	<stdio.h>

#define	oops(s)	{ perror(s); exit(1); }

main()
{
	int	pid;
	int	p[2];

	if ( pipe(p) == -1 )
		oops("pipe");

	pid = fork();
	if ( pid == -1 )
		oops("fork");

	/* in child, we need to be sort since noone cares */
	if ( pid == 0 )
	{
		if ( dup2(p[0],0) == -1 )/* make reading end stdin */
			oops("dup2");	
		execlp("sort","sort",NULL);
		perror("exec");
		exit(1);
	}

	/* in parent, we run who */

	if ( dup2( p[1], 1 ) == -1 )
		oops("dup2 in parent");
	execlp("who", "who",NULL );
	perror("exec by parent");
	exit(1);
}

