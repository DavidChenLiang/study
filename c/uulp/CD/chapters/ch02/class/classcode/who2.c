#include	<stdio.h>
#include	<sys/types.h>
#include	<utmp.h>
#include	<fcntl.h>
#include	<time.h>

/*
 *	who version 2		- read /etc/utmp and list info therein
 * 				- surpresses empty records
 *				- formats time nicely
 */

/* UTMP_FILE is a symbol defined in utmp.h */
/* #define	SHOWHOST */

main(int ac, char **av)
{
	struct utmp	utbuf;		/* read info into here */
	int		utmpfd;		/* read from this descriptor */

	if ( (utmpfd = open( UTMP_FILE, O_RDONLY )) == -1 ){
		fprintf(stderr,"%s: cannot open %s\n", *av, UTMP_FILE);
		exit(1);
	}

	while ( read( utmpfd, &utbuf, sizeof(utbuf) ) == sizeof(utbuf) )
		show_info( &utbuf );
	close( utmpfd );
}
/*
 *	show info()
 *			displays the contents of the utmp struct
 *			in human readable form
 *			* displays nothing if record has no user name
 */
show_info( struct utmp *utbufp )
{
	if ( utbufp->ut_type != USER_PROCESS )
		return;

	printf("%-8.8s", utbufp->ut_name);		/* the logname	*/
	printf(" ");					/* a space	*/
 	printf("%-8.8s", utbufp->ut_line);		/* the tty	*/
	printf(" ");					/* a space	*/
	showtime( utbufp->ut_time );			/* display time	*/
#ifdef SHOWHOST
	if ( utbufp->ut_host[0] != '\0' )
		printf(" (%s)", utbufp->ut_host);	/* the host	*/
#endif
	printf("\n");					/* newline	*/
}

showtime( time_t timeval )
/*
 *	displays time in a format fit for human consumption
 *	uses ctime to build a string then picks parts out of it
 *      Note: %12.12s prints a string 12 chars wide and LIMITS
 *      it to 12chars.
 */
{
	char	*ctime();		/* convert long to ascii	*/
	char	*cp;			/* to hold address of time	*/

	cp = ctime( &timeval );		/* convert time to string	*/
					/* string looks like		*/
					/* Mon Feb  4 00:46:40 EST 1991 */
					/* 0123456789012345.		*/
	printf("%12.12s", cp+4 );	/* pick 12 chars from pos 4	*/
}
