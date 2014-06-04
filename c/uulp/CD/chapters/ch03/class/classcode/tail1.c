#include	<stdio.h>

/*
 *	tail.c	version 1	unbuffered
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
	int	fd,		/* descriptor of file to tail		*/
		lines;		/* how many lines to print		*/
	void	tail();

	if ( ac != 2 ){				/* arg count check	*/
		fprintf(stderr, "usage: %s filename\n", *av);
		exit(1);
	}

	lines = DFL_LINES ;

	if ( ( fd = open( av[1] , 0 ) ) < 0 ){	/* open file		*/
		perror( av[1] );		/* oops			*/
		exit(2);
	}

	tail( fd , lines );			/* print tail		*/
	close( fd );				/* close it		*/
}

void
tail( fd , lines )
{
	char	c;			/* one char buffer		*/
	long	from0, fromend,		/* positions in file		*/
		lseek();		/* for moving through file	*/
	int	n_lines;		/* number of lines seen		*/
	int	rv;

	fromend = -2L; n_lines = 0;		/* don't count last nl	*/

	while ( n_lines < lines 			/* more lines	*/
		&& (from0=lseek(fd, fromend, 2)) >= 0 	/* && more file	*/
		&& (rv = read(fd,&c,1)) == 1 )		/* && ok reads	*/
	{
			if ( c == '\n' )		/* if newline	*/
				n_lines++;		/* inc counter	*/
			fromend--;			/* backup pos	*/
	}

	/* ... out of loop ... get to right place and copy		*/

	if ( from0 < 0 )			/* fell off end ? 	*/
		lseek( fd, 0L, 0);		/* oops. reposition	*/
	while ( read(fd, &c, 1 ) == 1 )		
		putchar( c );
}
