#include <stdio.h>
#include <malloc.h>

/*
 * envchange.c
 *	   what: shows that the environment is SIMPLY the array pointed
 *               to by the global variable called environ
 *	 method: change it to something else and then use getenv()
 */

char **environ;

main()
{
	char	*newenv[5];

	printf("The current environment is..\n");
	system( "showenv|more" );

	printf("\nPress return to continue..."); getchar();
	printf("***** Replacing entry 0 with MONTH=APRIL..\n"); getchar();
	environ[0] = "MONTH=April";
	system( "showenv|more" );

	printf("\nPress return to continue..."); getchar();
	printf("***** Now pointing environ to a new table..\n"); getchar();
	newenv[0] = "HOME=/on/the/range";
	newenv[1] = "LOGNAME=nobody";
	newenv[2] = "PATH=.:/bin:/usr/bin";
	newenv[3] = "DAY=Wednesday";
	newenv[4] = NULL ;
	environ = &newenv[0];		/* or environ = newenv */
	system( "showenv" );
}
