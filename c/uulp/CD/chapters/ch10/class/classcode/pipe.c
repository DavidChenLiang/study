#include	<stdio.h>

/**
 *	pipe.c		* Demonstrates how to create a pipeline from
 *			  one process to another
 *
 *			* Takes two args, each a command, and connects
 *			  av[1]'s output to input of av[2]
 *			* usage: pipe command1 command2
 *			  effect: command1 | command2
 *			* Limitations: commands do not take arguments
 *			* uses execlp() since known number of args
 *			* Note: exchange child and parent and watch fun
 **/

main(ac, av)
char **av;
{
	int	thepipe[2],			/* two file descriptors	*/
		newfd,				/* useful for pipes	*/
		pid;				/* and the pid		*/

	if ( ac != 3 ){
		fprintf(stderr, "usage: pipe cmd1 cmd2\n");
		exit(1);
	}
	if ( pipe( thepipe ) == -1 ){		/* get a pipe		*/
		perror( "cannot create pipe" );
		exit(1);			/* or exit		*/
	}

	/* ------------------------------------------------------------ */
	/*	now we have a pipe, now let's get two processes		*/

	if ( (pid = fork()) == -1 ){			/* get a proc	*/
		fprintf(stderr,"cannot fork\n");
		exit(1);				/* or exit	*/
	}

	/* ------------------------------------------------------------ */
	/* 	Right Here, there are two processes			*/
	/*
	 *	parent will read from reading end of pipe
	 */

	if ( pid > 0 ){			/* the child will be av[2]	*/
		close(thepipe[1]);	/* close writing end		*/
		close(0);		/* will read from pipe		*/
		newfd=dup(thepipe[0]);	/* so duplicate the reading end	*/
		if ( newfd != 0 ){	/* if not the new stdin..	*/
			fprintf(stderr,"Dupe failed on reading end\n");
			exit(1);
		}
		close(thepipe[0]);	/* stdin is duped, close pipe	*/
		execlp( av[2], av[2], NULL);
		exit(1);		/* oops				*/
	}

	/*
	 *	child will write into writing end of pipe
	 */
	close(thepipe[0]);	/* close reading end		*/
	close(1);		/* will write into pipe		*/
	newfd=dup(thepipe[1]);	/* so duplicate writing end	*/
	if ( newfd != 1 ){	/* if not the new stdout..	*/
		fprintf(stderr,"Dupe failed on writing end\n");
		exit(1);
	}
	close(thepipe[1]);	/* stdout is duped, close pipe	*/
	execlp( av[1], av[1], NULL);
	exit(1);		/* oops				*/
}
