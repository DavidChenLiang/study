#include	<stdio.h>

/**
 **	forkdemo1.c
 **
 **		shows how fork creates two processes, distinguishable
 **		by the different return values from fork()
 **/

main()
{
	int	ret_from_fork, my_pid;

	my_pid = getpid();			/* who am i?		*/
	printf("Hi, my pid is %d\n", my_pid );	/* tell the world	*/

	ret_from_fork = fork();

	sleep(1);
	printf("after fork().  It returned %d and my pid is %d\n", 
			ret_from_fork, getpid());
}
