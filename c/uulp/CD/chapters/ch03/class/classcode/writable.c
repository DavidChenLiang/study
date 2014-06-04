#include <sys/types.h>
#include <sys/stat.h>


main()
{
	struct stat fileinfoform;
	int modeval;

	stat( "/etc/passwd", &fileinfoform);

	printf(" The size of that file is %d\n", fileinfoform.st_size );
	printf(" The mode is %o\n", modeval = fileinfoform.st_mode );

	if ( modeval & 0200 ) 
		printf("writable by owner\n");
	else	
		printf("not writable by owner\n");

	if ( modeval & 0020 ) 
		printf("writable by group\n");
	else	
		printf("not writable by group\n");

	if ( modeval & 0002 ) 
		printf("writable by world\n");
	else	
		printf("not writable by world\n");
}
