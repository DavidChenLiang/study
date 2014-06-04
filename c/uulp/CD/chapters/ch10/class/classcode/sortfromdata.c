#include	<stdio.h>

/*
 * sortfromdata
 * this program will run the sort tool
 * reading stdin from a file called data
 * it will use the ideas we have
 * covered so far
 *
 */

main(int ac, char *av[])
{
	int	pid;

	pid = fork();		/* get a new process */

	if ( pid == -1 ){	/* check for errors	*/
		perror("fork");
		exit(1);
	}

	/* no errors yet, now... if the child .. */

	if ( pid == 0 )
	{
		close(0);		/* close stdin		*/
		if ( open(ac>1?av[1]:"data", 0) != 0 )
		{
			perror("open did not give us 0!");
			exit(1);
		}
		execlp("sort", "sort", "-r", NULL );
		perror("oops! execlp failed");
		exit(2);
	}

	/* else I am the parent and may as well...wait	*/

	wait(NULL);
	printf("all done!\n");
}
