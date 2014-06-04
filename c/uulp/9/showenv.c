#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

int
main(void){
    int i;
    for (i = 0; environ[i];i++){
        printf("%s\n", environ[i]);
    }
}
