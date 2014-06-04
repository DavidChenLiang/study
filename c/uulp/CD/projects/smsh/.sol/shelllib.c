#include	<stdio.h>
#include	"smsh.h"

/**
 **	shell lib	- some functions useful for writing a shell
 **			- based on code from Rochkind's Advanced 
 **			- Unix Programming,  chapter 5.
 **
 **		modified to return success or failure
 **			- added i_chdir() and i_read
 **			- added isaname()
 **/

/* ------------------------------------------------------------------*
 *	TYPES AND DEFS
 */
	

/* #define	VER7		/* for the ancient strchr / index problem */

/**
 **	assignment function
 **/

asg(argc, argv)
char **argv;
{
	char *charp, *name, *val;

	if ( argc != 1 ){
		fprintf(stderr,"Extra args\n");
		return 1;
	} else {
		name = charp = argv[0];
		while( *charp != '=' )
			charp++;
		*charp = '\0';
		val = charp+1;
		if ( !isaname(name) ){
			fprintf(stderr,"%s is not an identifier\n",name);
			return 1;
		}
		else if ( !EVset(name, val) ){
			fprintf(stderr,"Can't assign\n");
			return 1;
		}
	}
	return 0;
}

export(argc, argv)
char **argv;
/**
 **	called when command is export, if no args, the list envir vars
 **/
{
	int	i;

	if ( argc == 1 )
		return set(argc, argv);
	
	for(i = 1 ; i<argc; i++ )
		if ( !isaname(argv[i]) ){
			fprintf(stderr,"%s is not an identifier\n", argv[i]);
			return 1;
		}
		else if ( !EVexport(argv[i]) ){
			
			fprintf(stderr,"Can't export %s\n", argv[i]);
			return 1;
		}
	return 0;
}

set(argc, argv)
char *argv[];
{
	if ( argc != 1 ){
		fprintf(stderr,"Extra args\n");
		return 1;
	}
	else
	{
		EVprint();
		return 0;
	}
}


i_chdir(argc, argv)
char **argv;
{
	if ( argc != 2 ){
		fprintf(stderr,"chdir: Extra args\n");
		return 1;
	}
	if ( chdir( argv[1] ) == -1 ){
		fprintf(stderr,"%s: bad directory\n", argv[1]);
		return 1;
	}
	return 0;
}

i_read(argc, argv)
char **argv;
{
	char	buf[BUFSIZ];

	if ( argc != 2 ){
		fprintf(stderr,"read: arg count\n");
		return 1;
	}
	if ( !isaname(argv[1]) ){
		fprintf(stderr,"%s is not an identifier\n", argv[1]);
		return 1;
	}
	if ( fgets(buf, BUFSIZ, stdin) )
		buf[strlen(buf)-1] = '\0';
	else
		*buf = '\0';

	if ( !EVset(argv[1], buf) ){
		fprintf(stderr,"Can't assign\n");
		return 1;
	}
	return 0;
}
		

#ifdef	VER7
strchr(s,c)
char *s,c;
{
	char *index();
	return index(s,c);
}
#endif
