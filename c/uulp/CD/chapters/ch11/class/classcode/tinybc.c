#include	<stdio.h>

/**
 **	tc.c		* a tiny calculator that uses dc to do its work
 **			* demonstrates bidirectional pipes
 **			* input looks like number op number
 **			  which tc converts into number \n number \n op \n p
 **			  and passes result back to stdout
 **
 **		+-----------+                +----------+
 **	stdin  >0           >== pipetodc ====>          |
 **	        |    tc     |                |   dc -   |
 **	stdout <1           <== pipefromdc ==<          |
 **		+-----------+                +----------+
 **
 **			* The scheme is
 **				a. get two pipes
 **				b. fork (get another process)
 **				c. in the dc-to-be process,
 **					 connect stdin and out to pipes
 **					 then execl dc
 **				d. in the tc-process, no plumbing to do
 **					 just talk to human via normal i/o
 **					 and send stuff via pipe
 **				e. then close pipe and dc dies
 **
 **			 * The parent becomes dc..can you figure out why?
 **/

main()
{
	int	pid, pipetodc[2], pipefromdc[2];	/* equipment	*/

	/* -----------------------------------------------------------
	 *	get pipes before fork, so that both processes will
	 *	share the connection
	 */

	if ( pipe(pipetodc) == -1 || pipe(pipefromdc) == -1 ){
		perror("pipe failed");
		exit(1);
	}

	/* -----------------------------------------------------------
	 *	we got pipes, now to get a process for front end.
	 */

	if ( (pid = fork()) == -1 )
		fatal("could not fork");
	if ( pid == 0 )				/* child will be tc */
		be_tc(pipetodc, pipefromdc);
	else
		be_dc(pipetodc, pipefromdc);
}

be_dc(pipein, pipeout)
int pipein[2], pipeout[2];
/*
 *	set up stdin and stdout, then execl dc
 */
{
    /* setup stdin from pipein	*/
	close(0);
	if ( dup(pipein[0]) != 0 )	/* copy pipein[read] 	   */
		fatal("dc could not connect stdin to pipe");
	close(pipein[0]);		/* gonna read from stdin   */
	close(pipein[1]);		/* won't write to pipein   */

    /* setup stdout to pipeout	*/
	close(1);
	if ( dup(pipeout[1]) != 1 )	/* copy pipeout[write]	   */
		fatal("dc could not connect stdout to pipe");
	close(pipeout[1]);		/* gonna write to stdout   */
	close(pipeout[0]);		/* won't read from pipeout */

    /* now execl dc with the - option */
	execlp("dc", "dc", "-", NULL );
	fatal("couldnot exec dc");
}

be_tc(pipetodc, pipefromdc)
int pipetodc[2], pipefromdc[2];
/*
 *	read from stdin and convert into to RPN, send down pipe
 *	then read from other pipe and print to user
 *	Uses fdopen() to convert a file descriptor to a stream
 */
{
	int	num1, num2;
	char	operation[BUFSIZ], message[BUFSIZ], *fgets();
	FILE	*fpout, *fpin, *fdopen();

	close(pipetodc[0]);		/* won't read from pipe to dc  */
	close(pipefromdc[1]);		/* won't write to pipe from dc */

	fpout = fdopen( pipetodc[1],   "w" );	/* convert file desc-  */
	fpin  = fdopen( pipefromdc[0], "r" );	/* riptors to streams  */
	if ( fpout == NULL || fpin == NULL )
		fatal("Error convering pipes to streams");

	/*
	 * read from real stdin
	 */

	while (1){
		printf("tc: ");
		fflush(stdout);
		if ( fgets(message,BUFSIZ,stdin) == NULL )	/* get input */
			break;
								/* parse it */
		if ( sscanf(message, "%d%s%d", &num1,operation,&num2) != 3 ) {
			printf("syntax error\n");
			continue;
		}

		if ( fprintf( fpout , "%d  %d  %c  p\n", num1, num2, 
				*operation ) == EOF )
					fatal("Error writing");
		fflush(  fpout );
		if ( fgets( message, BUFSIZ, fpin ) == NULL )
			break;
		printf("%d %c %d = %s", num1, *operation , num2, message);
	}
	fclose(fpout);		/* close pipe		*/
	fclose(fpin);		/* dc will see EOF	*/
}

fatal( mess )
char *mess;
{
	fprintf(stderr, "Error: %s\n", mess);
	exit(1);
}
