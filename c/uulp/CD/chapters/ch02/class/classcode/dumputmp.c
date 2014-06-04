/* dumputmp.c 
 *
 *	purpose:	display contents of wtmp or utmp in readable form
 *	args:		none for default (/etc/utmp) or a filename
 *	action:		open the file and read it struct by struct,
 *			displaying all members of struct in nice columns
 *	compiling:	to compile this, use
 *			gcc dumputmp.c utmplib.c -o dumputmp
 */

#include	<stdio.h>
#include	<sys/types.h>
#include	<utmp.h>

main(int ac,char **av)
{
	if ( ac == 1 )
		dumpfile( UTMP_FILE );
	else
		dumpfile( av[1] );
}

dumpfile( char *fn )
/*
 * open file and dump records
 */
{
	struct utmp	*utp,		/* ptr to struct	*/
			*utmp_next();	/* declare its type	*/

	if ( utmp_open( fn ) == -1 )	/* open file		*/
	{
		perror( fn );
		return ;
	}

	/* loop, reading records and showing them */

	while( utp = utmp_next() )
		show_utrec( utp );
	utmp_close();
}
	
show_utrec( struct utmp *rp )
{
	char	*typename();

	printf("%-8.8s ", rp->ut_user );
	printf("%-8.8s ", rp->ut_id   );
	printf("%-8.8s ", rp->ut_line );
	printf("%6d ", rp->ut_pid );
	printf("%4d %-14.14s ", rp->ut_type , typename(rp->ut_type) );
	printf("%12d ", rp->ut_time );
	printf("%s", rp->ut_host );
	putchar('\n');
}

char *uttypes[] = {  	"EMPTY", "RUN_LVL", "BOOT_TIME", "OLD_TIME", 
			"NEW_TIME", "INIT_PROCESS", "LOGIN_PROCESS", 
			"USER_PROCESS", "DEAD_PROCESS", "ACCOUNTING"
	};

char *
typename( typenum )
{
	return uttypes[typenum];
}
