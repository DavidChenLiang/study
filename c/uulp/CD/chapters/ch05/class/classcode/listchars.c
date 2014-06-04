#include	<stdio.h>

/*
 *   listchars.c
 *      purpose: list individually all the chars seen on input
 *       output: char and ascii code, one pair per line
 *        input: stdin, until the letter Q
 *        notes: usesful to show that buffering/editing exists
 */

main()
{
	int	c, n = 0;

	while( ( c = getchar()) != 'Q' )
		printf("char %3d is %c code %d\n", n++, c, c );
}
