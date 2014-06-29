#include <stdio.h>
#include <fcntl.h>

#define CLOSE_UP
#define USE_DUP2

int
main(int argc, char ** args)
{
    int   fd;
    int   newfd;
    char  line[100];

    fgets(line, 100, stdin);printf("%s", line);
    fgets(line, 100, stdin);printf("%s", line);
    fgets(line, 100, stdin);printf("%s", line);
    fd  = open("data", O_RDONLY);
    #ifdef CLOSE_DUP
        close(0);
        newfd =dup(fd);
    #else
        newfd = dup2(fd,0);
    #endif
    if (newfd != 0){
        fprintf(stderr,"Could not duplicate fd to 0\n");
        exit(1);
    }
    close(fd);

    fgets(line, 100, stdin);printf("%s", line);
    fgets(line, 100, stdin);printf("%s", line);
    fgets(line, 100, stdin);printf("%s", line);
    
    
}
