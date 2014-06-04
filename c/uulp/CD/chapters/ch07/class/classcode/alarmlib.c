#include	<sys/time.h>
#include	<signal.h>

/*
 *	alarmlib.c	
 *			timer functions for higher resolution clock
 *
 *			set_ticker( number_of_milliseconds )
 *				arranges for the interval timer to issue
 *				SIGALRM's at regular intervals
 *			millisleep( number_of_milliseconds )
 *
 *	version 98.03.16
 */

extern int errno;

set_ticker( n_msecs )
/*
 *	arg in milliseconds, converted into micro seoncds
 */
{
	struct itimerval new_timeset, old_timeset;
	long	old;
	long	n_sec, n_usecs;

	n_sec = n_msecs / 1000 ;
	n_usecs = ( n_msecs % 1000 ) * 1000L ;

	new_timeset.it_interval.tv_sec  = n_sec;	/* set reload  */
	new_timeset.it_interval.tv_usec = n_usecs;	/* new ticker value */
	new_timeset.it_value.tv_sec     = n_sec  ;	/* store this	*/
	new_timeset.it_value.tv_usec    = n_usecs ;	/* and this 	*/

	if ( setitimer( ITIMER_REAL, &new_timeset, &old_timeset ) != 0 ){
		printf("Error with timer..errno=%d\n", errno );
		exit(1);
	}

}

static void my_handler();

millisleep( n )
{
	signal( SIGALRM , my_handler);	/* set handler		*/
	set_ticker( n );			/* set alarm timer	*/
	pause();				/* wait for sigalrm	*/
}
static void
my_handler()
{
	set_ticker( 0 );			/* turns off ticker */
}

