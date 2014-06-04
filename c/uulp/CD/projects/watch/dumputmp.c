#include	<stdio.h>
#include	<sys/types.h>
#include	<utmp.h>

main(ac,av)
char **av;
{
	if ( ac == 1 )
		dumpfile( UTMP_FILE );
	else
		dumpfile( av[1] );
}

dumpfile( fn )
char *fn;
/*
 * open file and dump records
 */
{
	struct utmp	utrec;
	int		fd;

	fd = open( fn, 0 );
	if ( fd == -1 )
	{
		perror( fn );
		return ;
	}
	while( read( fd, &utrec, sizeof(utrec) ) == sizeof(utrec) )
		show_utrec(&utrec);
	close( fd );
}
	
show_utrec( rp )
struct utmp *rp;
{
	char	*typename();

	printf("%-8.8s ", rp->ut_user );
	/* printf("%-14.14s ", rp->ut_id   ); /* used it for hp-ux */
	printf("%-12.12s ", rp->ut_line );
	printf("%6d ", rp->ut_pid );
	printf("%4d %-12.12s ", rp->ut_type , typename(rp->ut_type) );
	printf("%12d ", rp->ut_time );
	printf("%s ", rp->ut_host );
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
