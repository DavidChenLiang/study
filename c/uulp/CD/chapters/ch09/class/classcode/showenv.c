
/*
 *	showenv.c
 *
 *		demonstrates how to read the entire list
 *		of environment variables
 */


	extern char	**environ;

main()
{
	int	i;

	for( i = 0 ; environ[i] ; i++ )
		printf("%s\n", environ[i] );
}
