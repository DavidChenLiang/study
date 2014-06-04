#include	<signal.h>

/*
 * signal_demo2.c	95.03.10
 *
 * purpose: show how to install signal handlers, how to reset signal handlers,
 *	    and how a signal handler is passed the signal number
 */

main()
{
	int	catcher();

	signal(SIGINT, catcher);		/*call this function */
	signal(SIGQUIT, catcher);
	signal(SIGTERM, catcher);

	while(1){
		printf("hello, world\n");
		sleep(2);
	}
}

catcher(thenum)
{
	printf("nope, signal %d can't hurt me\n", thenum);
	signal(thenum, catcher);
}
