

#include	<stdio.h>

main(int ac, char *av[])
{
	if ( ac == 3 )
		if ( link( av[1], av[2] ) == -1 )
			perror("cannot link");
		else
			printf("success!\n");
	else
		printf("wrong number of args.\n");
}
