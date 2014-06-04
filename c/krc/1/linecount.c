#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int count  = 0;
    int c;
    while ( (c = getchar()) != EOF){
        if (c == '\n'){
            count ++;
        }
    }
    printf("line count is %d\n",count);
    return(EXIT_SUCCESS);
}
