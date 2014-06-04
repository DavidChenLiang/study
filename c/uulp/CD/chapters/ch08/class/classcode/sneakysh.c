#include	<stdio.h>

/*
 *	a sneaky way of writing a shell
 */


main()
{
	char	command_line[BUFSIZ];

	while( printf("$ ") != EOF && gets(command_line) )
		system( command_line );
}
