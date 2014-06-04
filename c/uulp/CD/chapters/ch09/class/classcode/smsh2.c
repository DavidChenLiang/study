#include	<stdio.h>
#include	<signal.h>
#include	"smsh.h"

/**
 **	small-shell version 2
 **		a small step up from smsh1
 **		this one displays result of command in detail
 **		(the report) function is the new item here
 **/

#define	MAXARG		20
#define	MAXCMDLEN	512
#define	DFL_PROMPT	"> "

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
}

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

