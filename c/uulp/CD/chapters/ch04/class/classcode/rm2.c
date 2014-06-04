

#include	<stdio.h>

main()
{
	char	name[100];
	char	confirm[100];

	while ( printf("delete what file? "), gets(name) )
	{
		printf("about to unlink %s, ok? ", name );
		gets(confirm);
		if ( *confirm == 'y' )
			if( unlink(name) == -1 )
				perror(name);
			else
				printf("%s is gone\n", name);
	}
}
