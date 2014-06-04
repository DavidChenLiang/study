#include	<stdio.h>


main(int ac, char *av[])
{
	while(--ac){
		if ( unlink( *++av ) == -1 )
			perror(*av);
		else
			printf("%s is gone\n", *av);
	}
}
