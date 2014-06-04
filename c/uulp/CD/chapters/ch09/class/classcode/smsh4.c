#include	<stdio.h>
#include	<signal.h>
#include	"smsh.h"
#include	"varlib.h"

/**
 **	small-shell version 4
 **		this one supports environment variables
 **		it loads variable table from environment
 **		it supports export and reloads environment before exec
 **/

#define	MAXARG		20
#define	MAXCMDLEN	512
#define	DFL_PROMPT	"> "

extern char **environ;

main()
{
	char	*argv[MAXARG + 1], *prompt, cmdline[MAXCMDLEN];
	int	argc;

	prompt = DFL_PROMPT ;
	signal(SIGINT,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if ( VLenviron2table(environ) == 0 )
		exit(1);

	while ( get_next_command( prompt, cmdline, stdin ) == TRUE ) {
		if ( splitline(cmdline, &argc, argv, MAXARG) == FALSE )
			continue;
		if ( built_in_command( argc, argv ) == FALSE )
			execute( argc, argv );
	}
}

built_in_command(int argc, char *argv[])
/*
 *	if a built-in, do it, else return FALSE
 */
{
	char	*cp;

	if ( (cp=strchr(argv[0], '=')) != NULL ){	/* var=val ?	*/
		*cp = '\0';				/* yes		*/
		VLstore(argv[0], cp+1);			/* add to vartab*/
		return TRUE;
	}
	if ( strcmp(argv[0], "set") == 0 ){		/* set command	*/
		VLset();				/* y: do it	*/
		return TRUE;
	}
	if ( strcmp(argv[0], "export") == 0 ){		/* export cmd?	*/
		VLexport(argv[1]);			/* need argc	*/
		return TRUE;				/* check here	*/
	}
	return FALSE;
}


get_next_command( prompt, buffer, input_stream )
char *prompt, *buffer;
FILE *input_stream;
/*
 *  read next line from input_stream.  Return FALSE on EOF
 */
{
	printf("%s", prompt);				/* prompt user	*/
	if ( fgets(buffer, MAXCMDLEN, input_stream) )	/* get line	*/
	{
		buffer[strlen(buffer) - 1] = '\0';	/* remove nl	*/
		return TRUE;				/* say ok	*/
	}
	return FALSE;					/* no more	*/
}

execute(argc, argv)
char *argv[];
/*
 *	argv is all set to pass to execvp, and argc is nice to know about
 *	but execvp uses the terminating NULL in argv.
 *	Note: VLtable2environ() uses malloc().  Why is this
 *	not a memory leak?
 */
{
	int	pid = fork();
	int	child_info;

	if ( pid == -1 )
		perror("fork");
	else if ( pid == 0 ){
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		environ = VLtable2environ();
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}
	else {
		if ( wait( &child_info) == -1 )
			perror("wait");
	}
}

