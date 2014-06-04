
#include	<stdio.h>
#include	"smsh.h"
#include	<signal.h>

/**
 **	execute( argc, argv )
 **
 **	checks for builtins and does em
 **	or tries to execvp()
 **/

execute(ac,av)
char **av;
{
	int	retval ;

	if ( builtin( ac, av , &retval ) == NO )
		retval = external( ac, av );

	return retval ;
}

external(ac,av)
char **av;
/*
 *	execute ac as a program
 */
{
	int	pid, childstat;

	switch ( pid=fork() ){

		case -1:
			fprintf(stderr,"cannot fork\n");
			return 1;
		case 0:
			if ( !EVupdate() )
				fatal("can't update environment");
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execvp(av[0], av);
			fatal("%s: not found", av[0]);
		default:
			while( wait(&childstat) != pid );
			return ( childstat );
	}
}

builtin( ac, av , rvp )
char **av;
int *rvp;
/*
 *	if av[0] is a builtin, then doit and put return value in *rvp
 *	and return YES. else return NO
 */
{
	if ( strchr(av[0], '=' ) )
		*rvp = asg(ac, av);

	else if ( strcmp(av[0],"export") == 0 )
		*rvp = export(ac, av);

	else if ( strcmp(av[0],"set") == 0 )
		*rvp = set(ac, av);

	else if ( strcmp(av[0], "cd") == 0 || strcmp(av[0],"chdir") == 0 )
		*rvp = i_chdir(ac,av);

	else if ( strcmp(av[0],"read") == 0 )
		*rvp = i_read(ac,av);

	else
		return NO;

	return YES ;
}

	
