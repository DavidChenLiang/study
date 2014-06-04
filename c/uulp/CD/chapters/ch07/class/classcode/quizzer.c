#include	<stdio.h>
#include	<signal.h>

/*
 * quizzer.c
 *		purpose	ask a question, wait for answer, timeout on inaction
 *		usage   quzzer question answer timeout
 *		returns	0 if correct, 1 if not correct, 2 if timeout, 3 EOF
 *		method	prints question, sets timer, waits for answer
 */

main(int ac, char *av[])
{
	void	on_timeout();
	char	ans[BUFSIZ];

	if ( ac != 4 ){
		fprintf(stderr,"usage: quzzer question answer timeout\n");
		exit(1);
	}

	signal( SIGALRM, on_timeout );		/* set handler		*/
	printf("%s? ", av[1] );
	alarm(atoi(av[3]));
	if ( fgets(ans, BUFSIZ, stdin) == NULL )
		return 3;

	/* got an answer with trailing newline, remove it then compare	*/
	ans[strlen(ans)-1] = '\0';		/* chop off newline	*/
	
	if ( strncasecmp( av[2], ans ) == 0 )	/* check answer		*/
		return 0;
	return 1;
}

/*
 * on_timeout, handler for SIGALRM,
 */

void
on_timeout()
{
	printf("TIMEOUT!\n");
	exit(2);
}
