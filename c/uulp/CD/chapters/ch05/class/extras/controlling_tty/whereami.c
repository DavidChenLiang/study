#include	<stdio.h>

main()
{
	char	*where;
	char	*ttyname();
	char	x;
	char	t[100];

	printf("fd 0 is at %s\n", ttyname(0) );
	printf("fd 1 is at %s\n", ttyname(1) );
	printf("fd 2 is at %s\n", ttyname(2) );
	x = open("/dev/tty", 0 );
	printf("ctermid says %s\n", ctermid(t));
	printf("I think I am at %s\n", ttyname(x));
}
