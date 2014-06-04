#include	<stdio.h>
#include	<fcntl.h>

main(ac, av)
char *av[];
{
	int	fd;
	long	where;
	char	a_character;

	fd = open( av[1], O_RDONLY );
	if ( fd == -1 ){
		perror(av[1]);
		exit(1);
	}
	
	where = -1 ;

	while( lseek( fd, where , 2 ) != -1 )
	{
		read( fd, &a_character, 1 );
		putchar( a_character );
		where--;
	}
}
