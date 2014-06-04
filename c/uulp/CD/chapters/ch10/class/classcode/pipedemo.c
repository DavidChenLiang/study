#include	<stdio.h>

/**
 **	pipedemo.c	* Demonstrates: how to create and use a pipe
 **			* Effect: creates a pipe, writes into writing
 **			  end, then runs around and reads from reading
 **			  end.  A little weird, but demonstrates the
 **			  idea.
 **
 **/

main()
{
	int	len, i,
		apipe[2];		/* two file descriptors */
	char	buf[BUFSIZ];		/* for reading end	*/

	/*
	 *	first, get a pipe from the operating system
	 */

	if ( pipe ( apipe ) == -1 ){
		perror("could not make pipe");
		exit(1);
	}
	printf("Got a pipe! It is file descriptors: { %d %d }\n", 
							apipe[0], apipe[1]);

	/*
	 *	then, write each arg down the pipe's writing end ( [1] )
 	 *	and read words back from the reading end
	 */

	while ( gets(buf) ){				/* get next line */
		len = strlen( buf );
		if (  write( apipe[1], buf, len) != len ){	/* send	*/
			perror("writing to pipe");		/* down */
			break;					/* pipe */
		}
		for ( i = 0 ; i<len ; i++ )
			buf[i] = 'X' ;
		len = read( apipe[0], buf, BUFSIZ ) ;		/* read */
		if ( len == -1 ){				/* from */
			perror("reading from pipe");		/* pipe */
			break;
		}
		if ( write( 1 , buf, len ) != len ){		/* send  */
			perror("writing to stdout");		/* to    */
			break;					/* stdout */
		}
		write( 1, "\n", 1 );
	}
}
