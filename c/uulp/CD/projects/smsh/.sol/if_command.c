#include	<stdio.h>
#include	"smsh.h"

/**
 **	if command handler
 **
 **	the static variables in this function store the
 **	state of the if command
 **
 **	input: an input line
 **	output: YES or NO
 **		YES -> execute this line
 **		NO  -> do not execute this line
 **
 **	if called, with NULL, then  check for premature EOF
 **
 **	note: does not nest.  Could be handled with a stack, but
 **	a recursive parser might be nicer.
 **/

#define	NO_IF		0		/* not in if		*/
#define	SAW_IF		1		/* saw if, want then	*/
#define	SAW_THEN	2		/* want else or fi	*/
#define	SAW_ELSE	3		/* want fi		*/

static int	if_mode = NO_IF;	/* initial state */
static int	laststat ;		/* do we do then or else ? */

if_check( cmd )
char *cmd ;
{
	char		*cp;

	/*
	 * 	special wrapup case
	 */

	if ( cmd == NULL ){
		if ( if_mode != NO_IF )
			syntax("EOF unexpected");
		return NO;
	}

	/*
	 *	is this a new if command?
	 */
	if ( strncmp(cmd, "if", 2 ) == 0 && ISBLANK(cmd[2]) ){
		if ( if_mode != NO_IF ){
			syntax("cannot nest if's");
			return NO;
		}
		/* otherwise, a real if command */
		for( cp = cmd+3 ; ISBLANK(*cp) ; cp++ )
			;
		if ( !*cp ){
			syntax("null command for if");
			return NO;
		}

		laststat = do_command( cp );
		if_mode  = SAW_IF ;
		return NO ;
	}

	/*
	 *	now, check for other keywords: then, else, fi
	 */

	if ( strcmp(cmd, "then") == 0 ){
		if ( if_mode != SAW_IF )
			syntax("`then' unexpected");
		else
			if_mode = SAW_THEN ;
		return NO;
	}

	if ( strcmp(cmd, "else") == 0 ){		/* else case	*/
		if( if_mode != SAW_THEN )
			syntax("`else' unexpectd");
		else
			if_mode = SAW_ELSE ;
		return NO;
	}

	if ( strcmp(cmd, "fi") == 0 ){
		if ( if_mode != SAW_THEN && if_mode != SAW_ELSE )
			syntax("`fi' unexpected");
		else
			if_mode = NO_IF ;
		return NO;
	}

	if ( if_mode == SAW_IF ){		/* still in if */
		laststat = do_command( cmd );
		return NO;
	}

	/*
	 *	regular stuff, execution depends on control and status
	 */

	if (	if_mode == NO_IF
		|| if_mode==SAW_THEN && laststat==0 
		|| if_mode==SAW_ELSE && laststat!=0
	)
		return YES;

	return NO;
}

syntax( msg )
char *msg;
{
	fprintf(stderr,"syntax error: %s\n", msg);
	if_mode = NO_IF ;
}
