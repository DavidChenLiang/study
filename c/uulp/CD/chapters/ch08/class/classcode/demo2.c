#include	<stdio.h>
#include	<signal.h>


main()
{
	int	what_fork_returned ;
	char	*arglist[2];
	int	return_val_from_wait, arg_to_wait;

	printf("my pid is %d\n", getpid());

	what_fork_returned = fork();

	if ( what_fork_returned == 0 )
	{
		sleep(4);
		printf("Oh,  I am the child.  My pid is %d\n", getpid());
		printf("I guess , I'll run ls..\n");
		arglist[0] = "ls";
		arglist[1] = 0;

		printf("my CURRENT ppid is %d\n", getppid());
		execvp(  "ls", arglist );

		printf("ooooo.  Something bad happend..\n");
	}

	else

	{
		printf("My child, pid %d, will now run ls for you\n",
				what_fork_returned);

		signal(SIGINT, SIG_IGN);
		alarm(2);
		return_val_from_wait = wait( &arg_to_wait );

		printf("wait returned %d\n", return_val_from_wait);
		printf("and the stuff at arg_to_wait is %d\n",
				arg_to_wait);
	}
}
