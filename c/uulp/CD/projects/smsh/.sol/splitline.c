#include	<stdio.h>
#include	"smsh.h"


/**
 **	int splitline( char *sourceline, char *arglist[] , listlen )
 **
 **	reads sourceline and builds (in arglist) a table of pointers 
 **	to start of tokens in sourceline.  Returns number of args in
 **	arglist or -1 if it overflows list.
 **
 **	splits at spaces and tabs but leaves quoted (with \ ) spaces
 **	alone (sort of, it eats the \'s )
 **
 **	Note: this puts nulls into sourceline
 **/


splitline( src , arglist , listlen )
char *src, *arglist[];
/*
 *	see description above
 */
{
	int	pos,				/* index in arglist[]	*/
		inword;				/* see K+R page 18	*/
	char	*cp,				/* ptr into src string	*/
		*destp,
		ch;				/* current char		*/

	pos = 0     ;				/* and index		*/
	inword = NO ;				/* and state		*/

	for (destp = cp = src ; ch = *cp  ; cp++ ){

		if ( ISBLANK(ch) )		/* word separator?	*/
		{
			if ( inword == YES )	/* in a word?		*/
			{
				inword = NO ;	/* no more		*/
				*destp++='\0';	/* close it		*/
			}
			continue;
		}

		if ( ch == '\\' && ISBLANK(cp[1]) ) /* a quoted BLANK?	*/
			ch = *++cp;		/* step onto it		*/

		if ( inword == NO )		/* starting a new word?	*/
		{
			inword = YES ;		/* now we are		*/
			if ( pos == listlen )	/* room for it?		*/
				return -1;	/* ixnay		*/
			arglist[pos++] = destp;	/* point to start of it	*/
		}
		*destp++ = ch ;			/* put char there	*/
	}
	*destp = '\0';				/* close destination	*/
	return pos ;
}
