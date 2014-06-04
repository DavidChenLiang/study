#include	<stdio.h>
#include	<termios.h>

/*
 * Study how tabs are handled on this system
 */

main(int ac, char *av[])
{
	struct termios t ;
	int	rv;

	if ( ac == 1 ){
		usage();
	}

	rv = tcgetattr(0, &t);
	if ( rv == -1 ){
		perror("tcgetattr");
		exit(1);
	}

	if ( strcmp(av[1], "tab3") ){
		t.c_oflag |= TAB3 ;		/* turn on expansion */
	}
	else if ( strcmp(av[1],"tab0") ){
		t.c_oflag &= ~TABDLY ;		/* turn 'em off		*/
	}
	else if ( strcmp(av[1],"tabs") ){
		t.c_oflag &= ~OXTABS ;
	}
	else if ( strcmp(av[1],"-tabs") ){
		t.c_oflag |= OXTABS ;
	}
	rv = tcsetattr(0, TCSANOW, &t);
	if ( rv == -1 ){
		perror("tcsetattr");
		exit(1);
	}
	printf("ok\n");
}

usage()
{
	printf("tab3 tab0 -tabs or tabs\n");
	exit(1);
}
