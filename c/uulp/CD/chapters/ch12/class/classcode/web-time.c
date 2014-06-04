#include	<time.h>

/*
 * 	function 	rfc822_time()
 *	purpose		return a string suitable for web servers
 *	details		Sun, 06 Nov 1994 08:49:37 GMT    
 *	method		use gmtime() to get struct
 *			then use asctime to translate to English
 *			Tue Nov	 9 15:37:29 1993\n\0
 *			012345678901234567890123456789
 *			then rearrange using sprintf
 *	arg		a time_t value 
 *	returns		a pointer to a static buffer
 */

char *
rfc822_time(time_t thetime)
{
	struct tm *t ;
	char	*str;
	int	d;
	static  char retval[36];
	
	t = gmtime( &thetime );		/* break into parts	*/
	str = asctime( t );		/* create string	*/
	d = atoi( str + 8 );
	sprintf(retval,"%.3s, %02d %.3s %.4s %.8s GMT", 
			str ,   d, str+4, str+20, str+11 );
	return retval;
}

#ifdef STANDALONE
main()
{
	printf ( "[%s]\n", rfc822_time( time(0L) ) );
}
#endif
