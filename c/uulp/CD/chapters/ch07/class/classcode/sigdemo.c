#include	<stdio.h>
#include	<signal.h>

/*
 * sigdemo.c
 *	purpose: show answers to signal question 
 *	question1: does the handler stay in effect after a signal arrives?
 *	question2: what if a signalX arrives while handling signalX?
 *      question3: what if a signalX arrives while handling signalY?
 *      question4: what happens to getc() when a signal arrives?
 */


main(int ac, char *av[])
{
	void	inthandler(int);
	void	quithandler(int);
	char	input[100];

	signal( SIGINT,  inthandler );		/* set trap		*/
	signal( SIGQUIT, quithandler );		/* set trap		*/

	do {
		printf("\nType a message\n");
		if ( gets(input) == NULL )
			perror("Saw EOF ");
		else
			printf("You typed: %s\n", input);
	} 
	while( strcmp( input , "quit" ) != 0 );
}

void
inthandler(int s)
{
	printf(" Received signal %d .. waiting\n", s );
	sleep(2);
	printf("  Leaving inthandler \n");
}

void
quithandler(int s)
{
	printf(" Received signal %d .. waiting\n", s );
	sleep(3);
	printf("  Leaving quithandler \n");
}
