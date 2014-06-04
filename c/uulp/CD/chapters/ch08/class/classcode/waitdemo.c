#include	<stdio.h>

/*
 *	 shows how wait() returns the pid of an exiting child
 *
 */

main()
{
	int	ret_from_fork,
		ret_from_wait;

	char	*args[4];
	int	child_status;


	printf(" about to fork....\n");

	ret_from_fork = fork();

	if ( ret_from_fork == -1 ){
		perror( "fork" );
		exit(1);
	}

	if ( ret_from_fork == 0 ){		/* the child	*/
		args[0] = "ps";
		args[1] = "x";
		args[2] = NULL ;
		printf("I am the child and will do ps\n");
		sleep(3);

		execvp( "ps", args );		/* do the command	*/
		perror( "execvp" );
		exit(1);
	}

	printf("Parent here, sleeping until child exits..\n");

	ret_from_wait = wait( &child_status );

	printf("wait returned a value of %d\n", ret_from_wait );
	printf("and the child process exited with code %d\n", child_status);
}
