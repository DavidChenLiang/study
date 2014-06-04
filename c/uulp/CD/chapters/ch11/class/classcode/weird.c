#include	<stdio.h>


main()
{
	FILE	*fp, *fdopen();
	int	c;

	fp = fdopen( 0 , "r" );

	printf("stdin is %x, and fp is %x\n", stdin, fp );
	while(  (c = getc( stdin ) ) != EOF )
	{
		putchar(c);
		c = getc( fp );
		if ( c == EOF )	
			break;
		putchar( c );
	}
}
