#include	<time.h>

/*
 * long2date.c
 *     Shows how a Unix time is a number of seconds since Jan 1, 1970
 *     Fun to guess the number of seconds from then until today.  Enter
 *     the number of seconds and see how close you get.
 */

main()
{
	long	ttt;
	char	*ctime();

	while( scanf("%ld", &ttt) == 1 )
		printf("that time is %s", ctime(&ttt));
}
