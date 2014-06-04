#include	<stdio.h>

/*
 * 	more version 0.2
 *	read and print 24 lines then pause for a few special commands
 */

#define	PAGELEN	24
#define	LINELEN	512

main( int ac , char *av[] )
{
	FILE	*fp, *fopen();

	if ( ac == 1 )
		do_more( stdin );
	else
		while ( --ac )
			if ( fp = fopen( *++av , "r" ) )
			{
				do_more( fp ) ; fclose( fp );
			}
			else
				exit(1);
}

do_more( FILE *fp )
/*
 *	read PAGELEN lines, then call see_more() for further instructions
 */
{
	char	line[LINELEN];
	int	num_of_lines = 0;

	while ( fgets( line, LINELEN, fp ) ){		/* more input	*/
		if ( num_of_lines == PAGELEN ) {	/* full screen?	*/
			if ( !see_more() )		/* y: wannasee?	*/
				break;			/*    n: scram	*/
			num_of_lines = 0;		/*    y: reset	*/
		}
		if ( fputs( line, stdout )  == EOF )	/* show line	*/
			exit(1);			/* or die	*/
		num_of_lines++;				/* count it	*/
	}
}

see_more()
/*
 *	print a message and wait for response
 *	n or q means no, space or y means more
 */
{
	int	c;

	printf("\033[7m more? \033[m");		/* reverse on a vt100	*/
	while( (c=getchar()) != EOF )			/* get response	*/
	{
		if ( c == 'n' || c == 'q' )		/* n and q -> N	*/
			return 0;
		if ( c == ' ' || c == 'y' )		/* SP and y ->Y	*/
			return 1;
	}
	return 0;
}
