#include	<stdio.h>
#include	"smsh.h"

/**
 **	splitline ( parse a line into an array of strings )
 **/

splitline(cmdline, argcp, argv, max)
char	*cmdline;
int	*argcp;
char	*argv[];
/*
 *	cmdline has a string of white-space separated tokens
 *	put the addresses of the tokens in the array argv[]
 *	put their number in *argcp and do not put more than max 
 *	in argv or suffer dire consequences!
 *	NOTE: this modifies cmdline
 *	returns FALSE on too many args or zero args.  TRUE for ok stuff
 */
{
	int i = 0, retval = FALSE ;
	char *cmdp = cmdline ;

	while ( i<=max ){			/* still room? 		*/
						/* skip leading space	*/
		while ( *cmdp == ' ' || *cmdp == '\t' )
			cmdp++;
						/* at end of string?	*/
		if ( *cmdp == '\0' )
			break;
						/* record string	*/
		argv[i++] = cmdp ;		/* and bump counter	*/
		
						/* move to end of word	*/
		while ( *++cmdp && *cmdp != ' ' && *cmdp != '\t' )
			;

		if ( *cmdp != '\0' )		/* past end of word	*/
			*cmdp++ = '\0';		/* terminate string	*/
	}
	if ( i > max )
		printf("Too many args\n");
	else if ( i > 0 ){
		argv[i] = NULL ;		/* mark end of array	*/
		*argcp = i;			/* and store argc	*/
		retval = TRUE ;			/* say ok		*/
	}
	return retval ;
}
