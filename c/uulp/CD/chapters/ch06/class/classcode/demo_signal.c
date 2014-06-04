#include	<stdio.h>
#include	<signal.h>

/**
 **	signal sampler
 **
 **		short program to demonstrate how
 **		signals can kill a process, bounce off a process
 **		or be caught by a process
 **/

main()
{
	int	catcher();		/* a function to call on CtrlC */
	int	i;

	printf("Case 1: no special arrangements..");
	for (i=0;i<10;i++){
		putchar('*');fflush(stdout);
		sleep(1);
	}
	putchar('\n');

	signal(SIGINT, SIG_IGN);	/* ignore INTerrupts	*/
	printf("Case 2: ignoring interrupts..");
	for (i=0;i<10;i++){
		putchar('*');fflush(stdout);
		sleep(1);
	}
	putchar('\n');

	signal(SIGINT, catcher);	/* handle interruptions	*/
	printf("Case 3: catching interrupts..");
	for (i=0;i<10;i++){
		putchar('*');fflush(stdout);
		sleep(1);
	}
	putchar('\n');
}

catcher()
{
	printf(" Ouch! \n");
	system("/bin/who");
	/* signal( SIGINT, catcher ); */
}
