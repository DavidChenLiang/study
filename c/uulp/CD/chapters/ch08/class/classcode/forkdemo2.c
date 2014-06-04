#include	<stdio.h>

main()
{
	int	what_fork_said;

	printf("I am about to fork...\n");

	what_fork_said = fork();

	if ( what_fork_said == 0 )
	{
		printf("I am the child process.  I am process id %d\n", getpid());
	}
	else if ( what_fork_said != -1 )
	{
		printf("I am the parent, my child is %d\n", what_fork_said);
	}
	else
		perror("fork");
}
