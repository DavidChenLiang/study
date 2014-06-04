#include	<stdio.h>
#include	<sys/types.h>
#include	<utmp.h>

/*
 * utmpcat.c
 *
 *	purpose:	copy a certain number of utmp records from stdin
 *	args:		starting record, ending record
 *	action:		parse command line args
 *			then use fread to buffer input
 */

main(ac,av)
char **av;
{
	if ( ac != 3 )
		fprintf(stderr,"usage: %s firstrec lastrec\n", av[0] );
	else
		copy_utmp_records( atoi(av[1]), atoi(av[2]) );
}

copy_utmp_records( int first, int last )
/*
 * use fread since it buffers
 */
{
	struct utmp	utrec;		/* one record buffer	*/
	int		recnum = 0;	/* a counter		*/

	while( recnum <= last && fread( &utrec, sizeof(utrec), 1, stdin) > 0 )
		if ( recnum++ >= first )
			fwrite( &utrec, sizeof(utrec), 1, stdout );
}
