#include	<stdio.h>
#include	<curses.h>
#include	<termios.h>
#include	<signal.h>

/**
 **	minimore version 2 - nicer version
 **		solves	(1) input from a pipeline	( /dev/tty )
 **			(2) ^C during reading		( signal   )
 **			(3) reverse video		( termlib  )
 **			(4) screensize			( termlib  )
 **
 **		exercise: get it to print % of file in message
 **				
 **	usage: mmore2 filename
 **/

int	cmd_fd = 0;		/* source of user commands	*/

main(int ac,char *av[])
{
	FILE	*fp, *fopen();

	initscr();				/* set up curses	*/
	cmd_fd = open( "/dev/tty", 0 );		/* allow pipelines	*/
	if ( ac == 1 )
		do_more( stdin );		/* from stdin		*/
	else
		while ( --ac )
			if ( fp = fopen( *++av , "r" ) ){
				do_more( fp );
				fclose( fp );
			}
		else
			fprintf(stderr, "cannot open %s\n", *av );
}

do_more( FILE *fp )
{
	int	lines_shown = 0 ;
	char	line[BUFSIZ];
	int	key, c, int_handler();		/* call if Ctrl-C	*/

	set_crmode_noecho();			/* put kbd in raw mode	*/
	signal( SIGINT, int_handler );		/* arrange for signals	*/
	clear();				/* clear screen		*/
	while ( fgets( line, BUFSIZ, fp ) ){
		if ( lines_shown == LINES-1 ){		/* screenful	*/
			standout(); addstr("  MORE  "); standend();
			refresh();
			key = getakey( "q ");		/* get input	*/
			addstr("\r               \r");	/* clear message */
			if ( key == 'q' )
				break;			/* quit		*/
			if ( key == ' ' ){		/* new page	*/
				lines_shown = 0 ;
				clear();
			}
		}
		addstr( line );	 			/* output line	*/
		refresh();
		lines_shown++;				/* count lines	*/
	}
	restore_tty();
	if ( key == 'q' )				/* and scram	*/
		exit(0);
}
getakey( char *charset )
/*
 *	read until EOF or a char in charset.  IF eof , return *charset
 */
{
	char	c;
	while ( read(cmd_fd, &c, 1) == 1 && !strchr(charset,c) )
		;
	return ( c == EOF ? *charset : c );
}

int_handler()
/*
 *	call on ctrl-C, put tty back to previous state, get out
 */
{
	restore_tty();
	exit(1);
}

struct termios orig_tty;

set_crmode_noecho()
/*
 *	set cmd_fd into raw, noecho mode
 */
{
	struct termios ttystate;
	tcgetattr(cmd_fd, &ttystate);		/* read settings	*/
	orig_tty = ttystate;			/* store it		*/
	ttystate.c_lflag    &= ~ICANON ;	/* no buffering		*/
	ttystate.c_lflag    &= ~ECHO   ;	/* no echos		*/
	ttystate.c_cc[VMIN] = 1	       ;	/* 1 char is enough	*/
	tcsetattr(cmd_fd, TCSANOW, &ttystate);	/* set 'em		*/
}
	
restore_tty()
/*
 * 	put tty back
 */
{
	refresh();
	tcsetattr(cmd_fd, TCSANOW, &orig_tty);	/* reset tty stuff	*/
	endwin();				/* and curses functions	*/
}
