#include	<stdio.h>

main()
{
	int	c;

	while ( (c = getchar()) != EOF )
		printf("and the next char is %c\n", c);
}
