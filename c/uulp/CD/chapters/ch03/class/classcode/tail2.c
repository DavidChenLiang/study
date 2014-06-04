
#include	<stdio.h>

/*
 *	tail.c	version 2	buffered with stdio
 *
 *		Function:  Print last ten lines of file.  
 *		  To add:  read command line for number of lines
 *		    Note:  does not work with stdin
 *		   Usage:  tail filename
 */

#define	DFL_LINES	10

main( ac, av )
char **av;
{
	FILE	*fp, *fopen();	/* stream to file to tail		*/
	int	lines;		/* how many lines to print		*/
	void	ftail();

	if ( ac != 2 ){				/* arg count check	*/
		fprintf(stderr, "usage: %s filename\n", *av);
		exit(1);
	}

	lines = DFL_LINES ;

	if ( ( fp = fopen( av[1] , "r" ) ) == NULL ){	/* open file	*/
		perror( av[1] );		/* oops			*/
		exit(2);
	}

	ftail( fp , lines );			/* print tail		*/
	fclose( fp );				/* close it		*/
}

void
ftail( fp , lines )
FILE *fp;
{
	int	c;			/* one char buffer: an INT	*/
	long	from0, fromend,		/* positions in file		*/
		fseek();		/* for moving through file	*/
	int	n_lines;		/* number of lines seen		*/

	fromend = -2L; n_lines = 0;		/* don't count last nl	*/

	while ( n_lines < lines 			/* more lines	*/
		&& (from0=fseek(fp, fromend, 2)) >= 0 	/* && more file	*/
		&& ( ( c = getc(fp) ) != EOF ) )	/* && ok reads	*/
	{
			if ( c == '\n' )		/* if newline	*/
				n_lines++;		/* inc counter	*/
			fromend--;			/* backup pos	*/
	}

	/* ... out of loop ... get to right place and copy		*/

	if ( from0 < 0 )			/* fell off end ? 	*/
		fseek( fp, 0L, 0);		/* oops. reposition	*/
	while ( ( c = getc(fp) ) != EOF )
		putchar( c );
}
