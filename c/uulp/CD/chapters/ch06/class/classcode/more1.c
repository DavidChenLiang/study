#include	<stdio.h>
#include	<termios.h>

/**
 **	minimore version 1: uses raw mode to get chars one by one
 **		prints SCREENLENGTH lines and then pauses for keyboard input
 **	usage: mmore1 filename
 **/

#define	SCREENLENGTH	23

main(int ac, char *av[])
{
	FILE	*fp, *fopen();

	if ( ac != 2 ){
		fprintf(stderr,"usage: mmore1 filename\n" );
		exit(1);
	}
	if ( (fp = fopen( av[1] , "r" )) != NULL ){
		do_more( fp );
		fclose( fp );
	}
	else
		fprintf(stderr, "cannot open %s\n", av[1] );
}

do_more( FILE *fp )
{
	int	key, c, lines_shown  = 0;
	char	line[BUFSIZ];
	
	set_crmode_noecho();
	
	while ( fgets( line, BUFSIZ, fp ) ){
		if ( lines_shown == SCREENLENGTH ){	/* screenful	*/
			printf("[ -- MORE -- ] ");
			fflush(stdout);			/* force message*/
			key = getakey( "q \n");		/* get input	*/
			printf("\r               \r");	/* clear message */
			if ( key == 'q' )
				break;			/* quit		*/
			if ( key == ' ' )		/* new page	*/
				lines_shown = 0 ;
			else if ( key == '\n' )
				lines_shown--;
		}
		fputs( line, stdout );			/* output line	*/
		lines_shown++;				/* count lines	*/
	}
	restore_tty();
}
getakey( char *charset )
/*
 *	read until EOF or a char in charset.  IF eof , return *charset
 */
{
	int	c;
	while ( (c = getchar()) != EOF && !strchr(charset,c) )
		;
	return ( c == EOF ? *charset : c );
}

struct termios orig_mode;

set_crmode_noecho()
{
	struct	termios	ttymode;		/* scratch struct	*/

	tcgetattr(0, &ttymode);
	orig_mode = ttymode ;
	ttymode.c_lflag &= ~ICANON;		/* no buffering		*/
	ttymode.c_lflag &= ~ECHO;		/* no echoing		*/
	ttymode.c_cc[VMIN] = 1;			/* 1 char is enough	*/
	tcsetattr(0, TCSANOW, &ttymode);	/* install now		*/
}

restore_tty()
{
	tcsetattr(0,TCSANOW,&orig_mode);
}
