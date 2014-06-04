#include	<stdio.h>
#include	<ctype.h>
#include	"smsh.h"

/**
 **	variable substitution function
 **
 **	eval( char *sourcestring, char *deststring , int destlen )
 **
 **	reads from sourcestring, writes to deststring, expanding $
 **	expressions where appropriate
 **
 **	all that this thing cares about is $'s and \'s
 **	converts \$ into $, leaves other \'s alone
 **
 **	returns length of destination or -1 if overflow
 **/

eval( src, dest , len )
char *src, *dest;
int len;
{
	int	pos;			/* position in destination   */
	char	ch ,			/* current char		     */
		*getvar(),		/* look up varname	     */
		*varval;		/* point to it with this     */

	pos = 0;
	while ( ch = *src++ )
	{
		if ( pos == len )			/* overflow? */
			return -1;			/* get out!  */
			
		if ( ch == '\\' )			/* \$ and \\ */
			if ( *src=='$' || *src=='\\' )	/* eat \     */
		{
			dest[pos++] = *src ;		/* copy char */
			src++;				/* advance   */
			continue;			/* nextchr   */
		}

		if ( ch != '$' )			/* EZ case   */
		{
			dest[pos++] = ch ;		/* write it  */
			continue;			/* next char */
		}

		/* else is a $, so we need to collect chars into a   */
		/* buffer, look up buffer name and write its value   */

		varval = getvar( &src );		/* moves src */
		if ( strlen(varval) + pos >= len )	/* overflow? */
			return -1;			/* too bad.. */

		strcpy(dest+pos, varval);		/* ok! write */
		pos += strlen(varval);			/* & advance */
	}
	dest[pos] = '\0';
	return pos ;
}

char *
getvar( srcp )
char **srcp;
/*
 *	srcp points to a pointer to a buffer
 *	Move that to collect identifier name, and then
 *		return pointer to the value.
 *	Note: if no legal letters after name, then return
 *		$ and leave *srcp unmoved.
 */
{
	char	varname[VARLEN+1];		/* gather chars here */
	int	pos;				/* index with this   */
	char	*cp, *EVget();			/* gen'l purpose ptr */

	cp  = *srcp ;				/* get read ptr      */
	pos = 0;				/* set write pos     */

	while ( is_an_idchar(*cp, pos) )	/* collect ok chars  */
		varname[pos++] = *cp++;		/* into varname	     */
	varname[pos] = '\0';			/* then close it up  */
	*srcp = cp ;				/* reset src ptr     */

	if ( pos > 0 )				/* got any ? 	     */
	{
		cp = EVget(varname);		/* then retrieve val */
		if ( cp == NULL )		/* if null, ret ""   */
			cp = "" ;		/* which is harmless */
	}
	else
		cp = "$";			/* else return the $ */

	return cp ;
}


isaname( s )
char *s;
/*
 *	checks if s is a valid name
 */
{
	int	pos = 0 ;
	while ( *s && is_an_idchar(*s, pos++) )
		s++;

	return ( !*s && pos );
}

is_an_idchar( ch , pos )
/*
 *	returns true or false depending if ch is ok as an identifier
 *	char in position   pos
 */
{
	return ( isalpha( ch ) || ch == '_' || ( isdigit( ch ) && pos > 0 ) );
}
