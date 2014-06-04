#include	<stdio.h>

/**
 **	pipedemo2.c	* Demonstrates how pipe is duplicated in fork()
 **			* Parent continues to write and read pipe,
 **			  but child also writes to the pipe
 **/

#define	CHILD_MESS	"I want a cookie"
#define	PAR_MESS	"testing.."

main()
{
	int	pipefd[2];		/* the pipe	*/
	int	len;			/* for write	*/
	char	buf[BUFSIZ];		/* for read	*/
	int	read_len;

	if ( pipe( pipefd ) == -1 ){
		perror("cannot get a pipe");
		exit(1);
	}

	switch( fork() ){
	
		case -1:
			fprintf(stderr,"cannot fork");
			exit(1);
	
		case 0:			/* child		*/
					/* write to pipe	*/
					/* every 5 seconds	*/
			len = strlen(CHILD_MESS);
			while ( 1 ){
				if (write( pipefd[1], CHILD_MESS, len) != len )
					exit(2);
				sleep(5);
			}

		default:		/* parent		*/
					/* read and write pipe	*/
			len = strlen( PAR_MESS );
			while ( 1 ){
				if ( write( pipefd[1], PAR_MESS, len)!=len )
					exit(3);
				sleep(1);
				read_len = read ( pipefd[0], buf, BUFSIZ );
				if ( read_len <= 0 )
					break;
				write( 1 , buf, read_len );
				write( 1, "\n", 1 );
			}
	}
}
