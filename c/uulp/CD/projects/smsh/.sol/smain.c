#include	<stdio.h>
#include	<signal.h>
#include	"smsh.h"

/**
 **	small-shell version 2
 **
 **	main module contains
 **		main()	
 **		mainloop()  - prompt, read, control, execute
 **		getcmd()    - input section
 **		docommand() - process, parse, execute
 **		setup()	    - initialize
 **		fatal()	    - quit in a hurry
 **/

main(ac, av)
char **av;
{
	setup(ac,av);
	mainloop();
}

mainloop()
/*
 *	issue prompt, get input line, examine command, do it
 */
{
	char	cmdline[MAXCMDLEN];		/* the current command	*/
	char	*sgprompt();			/* generates prompt	*/
	int	cmd_rv;				/* what getcmd says	*/

	while ( 1 ){

		printf("%s", sgprompt(NULL));	/* issue prompt		*/
		fflush(stdout);			/* get it to user	*/

		cmd_rv = getcmd( cmdline );	/* next command		*/

		if ( cmd_rv == EOF )		/* no more, get out	*/
			break;

		if ( cmd_rv == YES && if_check(cmdline) == YES )
			do_command(cmdline);	/* do it		*/
	}
	if_check(NULL);				/* tell if handler	*/
}


do_command(str)
char *str;
/*
 *	executes command, handles the if business
 *	if str is NULL, then program is wrapping up
 *		in this case, make sure that all if's are done
 */
{
	char		newstr[MAXCMDLEN];	/* after var subst	 */
	char		*arglist[MAXARG+1];	/* after tokenizing	 */
	int		argcount;		/* from tokenizing	 */
	int		retval ;		/* for assignment	 */

	/*
	 *	not a special command, like if so
	 *	expand variables and tokenize line
	 */

	if ( eval( str , newstr ,MAXCMDLEN ) == -1 )	/* overflow?	 */
	{
		fprintf(stderr,"line too long\n");
		return 1;
	}
	if ( (argcount = splitline( newstr, arglist, MAXARG ) ) == -1 )
	{
		fprintf(stderr,"too many args\n");
		return 1;
	}
	arglist[argcount] = NULL;

	/*
	 *	line all tokenized, ready to go
	 */

	return execute( argcount, arglist );
}

setup(ac,av)
char **av;
/*
 *	initialize system
 */
{
	FILE	*fp, *fopen();
	char	*prompt, *EVget();

	/* ...... set up input stream for commands .......... */

	if ( ac > 1 ){
		if ( (fp = fopen(av[1],"r")) == NULL )
			fatal("cannot open %s", av[1]);
		setinput(fp);
	}

	/* ...... set up environment ........................ */

	if ( !EVinit() )
		fatal("cannot initialize environment");

	/* ...... set up prompt ............................. */

	if ( ac > 1 || !isatty(0) || !isatty(1) )
		prompt = "" ;
	else if ( (prompt = EVget("PS2")) == NULL )
		prompt = DFL_PROMPT;
	sgprompt( prompt );

	/* ...... set up signals ............................ */

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/* ---------------------------------------------------------------- *

	Input section:	setinput() and getcmd()
			sgprompt()

 * ---------------------------------------------------------------- */

FILE	*cmdfp = stdin;

setinput(fp)
FILE *fp;
{
	cmdfp = fp ;
}

getcmd( buf )
char *buf;
/*
 *	read next command from cmdfp, return EOF on EOF
 *	return NO, on too many chars, or no chars
 *	and return YES elsewise
 *
 *	skips leading white space
 */
{
	int	c;

	do {
		if ( ( c = getc(cmdfp) ) == EOF )
			return EOF ;
		if ( c == '\n' )
			return NO ;
	} 
	while ( ISBLANK(c) );			/* skip leading blanks	 */

	buf[0] = c ;				/* put first char in buf */
	fgets( buf+1, MAXCMDLEN-1 , cmdfp );	/* read rest of line     */
	if ( buf[ strlen(buf)-1 ] != '\n' )	/* test for overflow	 */
		return NO ;			/* say so if it happens	 */
	
	buf[strlen(buf) - 1] = '\0';		/* zap newline		 */
	return YES ;				/* say ok to caller	 */
}

char *
sgprompt(newprompt)
char *newprompt;
{
	static char *cur_prompt = "> ";

	if ( newprompt )
		cur_prompt = newprompt ;
	return cur_prompt;
}

fatal(fmt, str)
char *fmt, *str;
{
	fprintf(stderr,"shell error: ");
	fprintf(stderr,fmt,str);
	putc('\n', stderr);
	exit(1);
}
