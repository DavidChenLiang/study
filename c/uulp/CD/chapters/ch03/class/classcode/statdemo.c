#include <sys/types.h>
#include <sys/stat.h>


main()
{
	struct stat fileinfoform;

	stat( "/etc/passwd", &fileinfoform);

	printf(" The size of that file is %d\n", fileinfoform.st_size );
}
