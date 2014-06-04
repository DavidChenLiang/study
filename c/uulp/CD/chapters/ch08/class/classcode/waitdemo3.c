#include	<stdio.h>
#include	<signal.h>

/*
 * shows how child can be killed and
 * and parent catches it
 *
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
		printf("I am the child and repeat myselft...");
		while (  1 ) {
			printf("hello\n");
			sleep (1 ) ;
		}
		exit(17);
	}

	printf("Parent here, sleeping until child exits..\n");

	signal(SIGINT,SIG_IGN);
	ret_from_wait = wait( &child_status );

	printf("wait returned a value of %d\n", ret_from_wait );
	printf("and the child process exited with code %x\n", 
			child_status  );
}
