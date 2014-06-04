#include <stdio.h>
#include <stdlib.h>

int
main(void)
{   
    int lin_num = 1;
    char *input;
    printf("Please input:\n");
    while (scanf("%s",input) != 0){
        printf("line %d:%s",lin_num++,input);
    }
    return(EXIT_SUCCESS);
}
