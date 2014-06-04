#include	<stdio.h>
#include	<fcntl.h>

/*
 * nosuchfile.c  - shows need for O_CREAT and some other flags
 */

#define	BIG_ENOUGH	200

main()
{
	char	filename[BIG_ENOUGH];
	int	fd;
	extern	errno ;

	printf("What file shall I write to? ");
	gets( filename );

	fd = open( filename, O_WRONLY , 07777 );
	if ( fd == -1 )
	{
		printf("oops..bad open, errno is %d\n", errno );
		perror(filename);	/* say what went wrong */
		exit(1);
	}
	write( fd , "hello\n", 6 );
	close( fd );
}
