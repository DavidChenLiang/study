#include	<stdio.h>

main()
{
	char	mydir[BUFSIZ];

	mygetcwd( mydir );
	printf(" We are in %s\n", mydir);
}

mygetcwd( buf )
char *buf;
{
	FILE *fp,*fopen();

	system("pwd > /tmp/whereIam");
	fp = fopen("/tmp/whereIam","r");
	fscanf(fp, "%s", buf);
	fclose(fp);
	unlink("/tmp/whereIam");
}
