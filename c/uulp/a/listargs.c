#include <stdio.h>

int
main(int argc, char ** argv)
{
    int i;
    
    printf("Numer of args, %d, Args are :\n",argc);
    for (i = 0; i<argc; i++){
        printf("args[%d] %s\n", i, argv[i]);
       }
    fprintf(stderr,"This message is sent to stderr.\n");
    return 0;
}
