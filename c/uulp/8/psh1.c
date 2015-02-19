#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define  MAXARGS  20
#define  ARGLEN   100 
int
main(void)
{
    char * arglist[MAXARGS+1];
    int  numargs;
    char argbuf[ARGLEN];
    char * makeString();
    int execute(char **);

    numargs = 0;
    
    while ( numargs < MAXARGS ) {
	printf ( "ARG[%d]?",numargs );
	
	if ( fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n') {
	    arglist[numargs++] = makeString(argbuf);
	}else{

	    if (numargs > 0 )
	    {
		arglist[numargs] = NULL;
		execute(arglist);
		printf("i am done.");
		numargs = 0;
	    }
	}
    }
    return EXIT_SUCCESS;

}
int
execute(char * arglist[])
{
    execvp(arglist[0],arglist);
    perror("execvp failed");
    exit(EXIT_FAILURE);
}
char *
makeString(char * buf)
{

    char * cp;
    buf[strlen(buf) - 1] = '\0';
    cp = malloc(strlen(buf) +1);
    if (cp  == NULL)
    {
	fprintf(stderr,"no memeory\n");
	exit(EXIT_FAILURE);
    }
    strcpy(cp, buf);
    return cp;
}

