#include	<stdio.h>

/**
 **	pipedemo3.c	* Demonstrates how pipe is duplicated in fork()
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
	int	times ;
	int	child_death_status;

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
			times = 5 ;
			len = strlen(CHILD_MESS);
			close(pipefd[0]);
			while ( times-- ){
				if (write( pipefd[1], CHILD_MESS, len) != len )
				{
					perror("write on pipe failed");
					exit(2);
				}
				sleep(2);
			}
			write(pipefd[1], "bye\n", 4);
			close(pipefd[1]);
			exit(0);

		default:		/* parent		*/
					/* read and write pipe	*/
			close( pipefd[1] );
			len = strlen( PAR_MESS );
			times = 3 ;	/* all i'll take from that pipe */
			while ( times-- ){
				/*if ( write( pipefd[1], PAR_MESS, len)!=len )
					exit(3); */
				read_len = read ( pipefd[0], buf, BUFSIZ );
				if ( read_len == 0 ){
					printf("say EOF on pipe.bye\n");
					exit(0);
				}
				if ( read_len < 0 ){
					perror("read on pipe");
					exit(1);
				}
				write( 1 , buf, read_len );
				write( 1, "\n", 1 );
			}
			close(pipefd[0]);
			wait(&child_death_status);
			printf("child died with %d\n", child_death_status);
			exit(0);
	}
}
