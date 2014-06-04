#include	<stdio.h>
#include	<signal.h>

/*
 * sleep1.c
 *		purpose	show how sleep works
 *		usage	sleep1
 *		info	sets handler, sets alarm, pauses, then returns
 */

// #define	SHHHH

main()
{
	void	onbell();

	printf("about to sleep for 4 seconds\n");
	signal(SIGALRM, onbell);			/* catch it	*/
	alarm(4);					/* set clock	*/
	pause();					/* do nothing	*/
	printf("Morning so soon?\n");			/* back to work	*/
}

void
onbell()
{
#ifndef SHHHH
	printf("Alarm received from kernel\n");
#endif
}
