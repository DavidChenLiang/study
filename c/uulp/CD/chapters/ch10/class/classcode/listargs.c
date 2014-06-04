#include	<stdio.h>

/* listargs.c
 *              print the number of command line args, list them,
 *		then print a message to stderr
 */

main( int ac, char *av[] )
{
	int	i;

	printf("Number of args: %d, Args are:\n", ac);
	for(i=0;i<ac;i++)
		printf("%s\n", av[i]);

	fprintf(stderr,"This message is sent to stderr.\n");
}
