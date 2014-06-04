#include	<stdio.h>

/*
 * implementing who|sort, step by step
 */

main()
{
	int	p[2];
	int	pid;

	if ( pipe(p) == -1 ){			/* get a channel */
		perror("pipe");
		exit(1);
	}

	pid = fork();				/* get a process	*/

	if ( pid == -1 ){			/* ok? */
		perror( "fork" );
		exit(2);
	}

	/* we need to behave differently in the different processes */

	if ( pid != 0 )			/* parent will be who */
	{
		close( p[0] );		/* close reading end */
		close( 1 );		/* prepare to redir stdout */
		if ( dup(p[1]) != 1 )
			exit(1);
		close( p[1] );
		execlp( "who", "who", NULL );
		perror( "execlp" );
		exit(1);
	}
	else				/* child will be sort */
	{
		close( p[1] );		/* let parent write into pipe */
		close(0);		/* prepare to redirect stdin */
		if ( dup(p[0]) != 0 )
			exit(99);
		close(p[0]);
		execlp( "sort", "sort", NULL );
		perror( "execlp for sort");
		exit(1);
	}
}
