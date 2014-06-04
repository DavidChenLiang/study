
#include	<stdio.h>
#include	<errno.h>


/*
 * program   perror_demo2.c
 * purpose   show how errno is set by syscalls
 *           and how perror prints the associated message
 *   usage   perror_demo
 *   action  tries to open() a file for a given mode
 *           then, if error, prints errno and message
 * NEW!!     add timestamp
 */

main()
{
	char	name[100];			/* filename		*/
	int	mode;				/* second arg to open	*/
	char	msg[512];
	long	now;

	printf("Open what file or dir? "); 
	gets(name);
	printf("   Open %s for 0,1, or 2? ", name);
	scanf("%d", &mode);
	if ( open( name, mode ) == -1 ){
		printf("Oh No!, errno %d just occurred\n", errno);
		now = time(NULL);
		sprintf(msg,"%.25s %s", ctime(&now), name);
		perror( msg );			/* print message	*/
	}
	else
		printf("%s opened ok\n", name );
}
