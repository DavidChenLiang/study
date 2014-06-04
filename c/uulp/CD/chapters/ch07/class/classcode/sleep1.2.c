#include	<stdio.h>
#include	<signal.h>

/*
 * sleep1.c
 *		purpose	show how sleep works
 *		usage	sleep1
 *		info	sets handler, sets alarm, pauses, then returns
 */

main()
{
	void	handler();

	printf("about to sleep for 4 seconds\n");
	signal(SIGALRM, handler);			/* catch it	*/
	alarm(4);					/* set clock	*/
	printf("Morning so soon?\n");			/* back to work	*/
}

void
handler()
{
	printf("Alarm received from kernel\n");
}
