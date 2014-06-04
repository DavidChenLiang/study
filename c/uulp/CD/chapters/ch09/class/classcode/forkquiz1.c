#include	<stdio.h>
#include	<signal.h>

/*
 *	forkquiz1.c
 *
 *		what does this program do in the following cases:
 *		a) user input, b) Ctrl-C, c) timeout
 */

main()
{
	int	child_status;
	int	retval;

	switch( fork() ) {
		case -1:
			perror("fork");
			exit(1);
		case  0:	
			alarm(10);	/* what if this were before fork? */
			printf("Child here.  Exit with what value? ");
			scanf("%d", &retval);
			exit(retval);
		default:
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			printf("parent waiting for child\n");
			wait( &child_status );
			printf("Status from child is:  %4d\n",  child_status);
			printf("              in hex:  %04x\n", child_status);
			printf("     as three fields: [xxxxxxxxcsssssss]\n");
			printf("                       %8d%d%7d\n", 
							child_status>>8, 
							(child_status>>7) & 1,
							child_status & 0x7F
				);
			printf(" x: value from eXit(), ");
			printf("C: coredump flag, s: signal number\n");
	}
}

