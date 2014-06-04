
#include	<stdio.h>
#include	<signal.h>

/**
 **	prompting shell version 2
 **
 **		Solves the `one-shot' problem of version 1
 **			Uses execvp(), but fork()s first so that the
 **			shell waits around to perform another command
 **		New problem: shell catches signals.  Run vi, press ^c.
 **/

#define	MAXARGS		20				/* cmdline args	*/
#define	ARGLEN		100				/* token length	*/
#define	CMDPROMPT	"Command please: "		/* prompts	*/
#define	ARGPROMPT	"next argument please: "
#define	prompt(n)	printf("%s", (n)==0 ? CMDPROMPT : ARGPROMPT );

main()
{
	char	*arglist[MAXARGS+1];		/* an array of ptrs	*/
	int	numargs;			/* index into array	*/
	char	argbuf[ARGLEN];			/* read stuff here	*/
	char	*makestring();			/* malloc etc		*/

	numargs = 0;
	while ( numargs < MAXARGS )
	{					
		prompt( numargs );	/* prompt user for arg	*/

					/* if arg, add to list	*/
		if ( gets(argbuf) && *argbuf ) {
			arglist[numargs++] = makestring(argbuf);
		}
		else
		{
					/* done, exit or execute cmd	*/
			if ( numargs == 0 )		/* no command?	*/
				break;			/* y: get out	*/
			arglist[numargs] = NULL ;	/* close list	*/
			execute( arglist );		/* do it	*/
			numargs = 0;			/* and reset	*/
		}
	}
	return 0;
}

execute( char *arglist[] )
/*
 *	use fork and execvp and wait to do it
 */
{
	int	pid,exitstatus;				/* of child	*/

	pid = fork();					/* make new process */
	switch( pid ){
		case -1:	
			perror("fork failed");
			exit(1);
		case 0:
			execvp(arglist[0], arglist);		/* do it */
			perror("execvp failed");
			exit(1);
		default:
			while( wait(&exitstatus) != pid )
				;
			printf("child exited with status %d,%d\n",
					exitstatus>>8, exitstatus&0377);
	}
}
char *
makestring( char *buf )
{
	char	*cp, *malloc();
	if ( cp = malloc( strlen(buf) + 1 ) )		/* get mem	*/
	{
		strcpy(cp, buf);			/* copy chars	*/
		return cp;				/* return ptr	*/
	}
	fprintf(stderr,"out of memory\n");
	exit(1);
}
