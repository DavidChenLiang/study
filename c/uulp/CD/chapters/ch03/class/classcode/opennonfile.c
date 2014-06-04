#include	<stdio.h>
#include	<fcntl.h>

/*
 * demo: show what happens when we try to open for writing
 *       a file that does not exist
 */


main()
{
	char	name[100];		/* file name goes here 	*/
	int	fd;			/* a fd for open	*/

	printf("file name? ");
	gets( name );			/* get the name		*/

	fd = open ( name, O_WRONLY|O_CREAT, 0644 );	/* we're going to write	*/
	if ( fd == -1 ){
		perror( name );
		exit( 1 );
	}
	/*
	 * other wise, put stuff in it
	 */
	
	if ( lseek( fd, 0, 2 ) == -1 )
	{
		perror( "lseek") ;
		exit(3);
	}

	if ( write ( fd, "stuff\n", 6 )  == -1 )
	{
		perror( "write" );
		exit (2);
	}

	close( fd );
	printf("success!\n");
}
