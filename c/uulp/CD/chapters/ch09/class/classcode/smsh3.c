#include	<stdio.h>
#include	<signal.h>
#include	"smsh.h"
#include	"varlib.h"

/**
 **	small-shell version 3
 **		the first version with local variables (uses varlib.c)
 **		includes the = operator and the set command
 **		no ability to use these in commands, yet
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
		if ( built_in_command( argc, argv ) == FALSE )
			execute( argc, argv );
	}
	return 0;
}

int
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
	return FALSE;
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
		else
			report(child_info);
	}
	return child_info;
}

int
report( int info )
/*
 * prints out result of child process
 */
{
	int	from_exit, core_flag, signal_num;

	signal_num = info & 0x7F ;
	core_flag  = (info >> 7 ) & 1;
	from_exit  = (info >> 8) ;

	if ( signal_num != 0 ){
		printf("\n[child died from signal %d]", signal_num);
		if ( core_flag ) printf(" (core dumped)" );
	}
	else
		printf("\n[child exited with code %d]", from_exit);
	putchar('\n');
}

