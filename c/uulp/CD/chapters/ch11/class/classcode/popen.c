#include	<stdio.h>
#include	<signal.h>

/**
 **	popen.c		* a version of the Unix popen() library function
 **
 **	FILE *popen( char *command, char *mode )
 **			command is a regular shell command
 **			mode is "r" or "w" 
 **			returns a stream attached to the command
 **			   or NULL
 **			execls "sh" "-c" command
 **
 **	exercise: what do we need a special pclose()? what would it do?
 **/

#define	READ	0
#define	WRITE	1

FILE *
popen(command, mode)
char *command, *mode;
{
	int	pfp[2], pid;		/* the pipe and the process	*/
	FILE	*fdopen(), *fp;		/* fdopen makes a fd a stream	*/
	int	par_end, chld_end;	/* of pipe 			*/

	if ( *mode == 'r' )		/* figure out direction		*/
		par_end = READ , chld_end = WRITE ;
	else if ( *mode == 'w' )
		par_end = WRITE, chld_end = READ ;
	else return NULL ;

	if ( pipe(pfp) == -1 || (pid = fork()) == -1 )	/* get a pipe	*/
		return NULL ;			/* and a process	*/

	/*
	 *	if parent, need to close one end and fdopen other end
	 */

	if ( pid > 0 ){	
		if (close( pfp[chld_end] ) == -1 )
			return NULL;
		return fdopen( pfp[par_end] , mode );	/* same mode */
	}

	/*
	 *	else, this is run by the child. It has to adjust
	 *	stdin or stdout and exec the command
	 */

	signal(SIGINT, SIG_IGN);		/* let parent decide	*/
	signal(SIGQUIT, SIG_IGN);		/* about signals	*/

	if ( close( pfp[par_end] ) == -1 )	/* close the other end	*/
		exit(1);			/* do NOT return	*/

	if ( close( chld_end ) == -1 )		/* close standard fd	*/
		exit(1);

	if ( dup( pfp[chld_end] ) != chld_end )	/* dup pipe to that fd	*/
		exit(1);

	if ( close( pfp[chld_end] ) == -1 )	/* done with this one	*/
		exit(1);

						/* all set to run cmd	*/
	execl( "/bin/sh", "sh", "-c", command, NULL );
	exit(1);
}
