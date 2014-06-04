#include	<stdio.h>
#include	<fcntl.h>
#include	<utmp.h>

/*
 *	who version 0
 *
 *		main outline but no substance
 */

main()
{
	int	fd;			/* for file des of utmp */
	struct utmp current_record;	/* hold info from file */
	int	reclen = sizeof(struct utmp);


	fd = open( UTMP_FILE, O_RDONLY );
	if ( fd == -1 )
	{
		perror( "who0" );
		exit(1);
	}

	while ( read ( fd , &current_record , reclen ) == reclen )
		show_info( &current_record );

	close ( fd );
}
