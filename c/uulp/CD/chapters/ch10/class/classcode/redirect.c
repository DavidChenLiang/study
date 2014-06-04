#include	<stdio.h>
/**
 **	redirect.c	* Demonstrates how a program (like the shell)
 **			  redirects input from a file for another program
 **
 **			* first arg is name of file to use for stdin
 **			  rest of args is command line
 **
 **			* usage:  redirect filename cmd [arg  ..]
 **	  		  equivalent to   cmd [arg ..] < filename
 **
 **			* exercise: convert this to redirect output, too
 **/
#define	TRUE	1
#define	FALSE	0

main( ac , av )
char **av;
{
	if ( ac < 3 ){
		fprintf( stderr, "usage: redirect filename cmd [arg..]\n");
		exit(1);
	}
	if ( setstdin( av[1] ) == FALSE )
		exit(1);

	run_command( ac-2 , av+2 );		/* this will exec */
}

run_command(ac, av)
char **av;
/**
 **	run the command and args in av.  convert to null-terminated array
 **	no return.  should just exec.
 **/
{
	char	**newav, *malloc();
	int	i;

	if ( ( newav=(char **) malloc((ac+1) * sizeof ( char * )) ) == NULL ){
		fprintf(stderr, "redirect: out of memory\n");
		exit(1);
	}
	for (i=0;i<ac;i++)			/* copy current args	*/
		newav[i] = av[i];
	newav[i] = NULL ;			/* and NULL terminate	*/

	execvp( av[0] , newav );		/* run new program	*/
	perror( "Cannot exec command" );	/* or tell why		*/
	exit(2);				/* and exit		*/
}

setstdin( fname )
char *fname ;
/*
 *	set standard input (fd 0) to named file
 *	returns TRUE if it worked, else returns FALSE
 */
{
	int	newfd;			/* result of open, should be 0	*/
	int	retval = FALSE ;	/* pessimism			*/

	close( 0 ) ;			/* ignore error if not open	*/
	newfd = open( fname , 0 );	/* open the file. should be 0	*/
	if ( newfd == -1 )		/* oops	*/
		perror( fname );	/* system tells what's wrong	*/
	else if ( newfd != 0 )		/* didn't work.. hmm	*/
		fprintf( stderr, "New file was not 0..\n" );
	else
		retval = TRUE ;		/* it worked!			*/
	return retval ;
}
