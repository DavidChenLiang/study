#include	<stdio.h>
#include	<signal.h>

/**
 **	prompting shell version 1
 **
 **			Prompts for the command and its arguments.
 **			Builds the argument vector for the call to execvp.
 **			Uses execvp(), and never returns.
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
 *	use execvp to do it
 */
{
	execvp(arglist[0], arglist);			/* do it */
	perror("execvp failed");
	exit(1);
}

char *
makestring( char *buf )
{
	char	*cp, *malloc();
	if ( cp = malloc( strlen(buf) + 1 ) ){		/* get mem	*/
		strcpy(cp, buf);			/* copy chars	*/
		return cp;				/* return ptr	*/
	}
	fprintf(stderr,"out of memory\n");
	exit(1);
}

