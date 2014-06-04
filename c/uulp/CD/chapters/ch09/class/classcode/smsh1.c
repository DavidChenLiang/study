#include	<stdio.h>
#include	<signal.h>
#include	"smsh.h"

/**
 **	small-shell version 1
 **		first really useful version after prompting shell
 **		this one parses the command line into strings
 **		uses fork, exec, wait, and ignores signals
 **/

#define	MAXARG		20
#define	MAXCMDLEN	512
#define	DFL_PROMPT	"> "

int
main()
{
	char	*argv[MAXARG + 1], *prompt, cmdline[MAXCMDLEN];
	int	argc;

	prompt = DFL_PROMPT ;
	signal(SIGINT,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	while ( get_next_command( prompt, cmdline, stdin ) == TRUE ) {
		if ( splitline(cmdline, &argc, argv, MAXARG) == FALSE )
			continue;
		execute( argc, argv );
	}
	return 0;
}

int
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

int
execute(argc, argv)
char *argv[];
/*
 *	argv is all set to pass to execvp, and argc is nice to know about
 *	but execvp uses the terminating NULL in argv.
 */
{
	int	pid = fork();
	int	child_info;

	if ( pid == -1 )
		perror("fork");
	else if ( pid == 0 ){
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}
	else {
		if ( wait( &child_info) == -1 )
			perror("wait");
	}
	return child_info;
}

