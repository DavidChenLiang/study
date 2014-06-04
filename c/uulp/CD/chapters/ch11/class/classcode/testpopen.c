#include	<stdio.h>

/**
 **	A little shell that runs commands and
 **	prints their output
 **/

main()
{
	FILE	*fp, *popen();
	char	buf[BUFSIZ];

	while ( printf("command please..") , gets(buf) ) {
		if ( !*buf )
			continue;
		if ( (fp = popen(buf,"r")) != NULL ){
			while ( fgets(buf, BUFSIZ, fp) )
				fputs(buf, stdout);
			fclose(fp);
		}
		else
			printf("Cannot execute %s\n", buf);
	}
}
