#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int in = 1;
    int word_count = 0;
    char c;
    while ((c = getchar()) != EOF){
        if (in){
            if (c == ' '){
                in = 0;
            }else{
                ;
            }
        }else{
            if (c == ' '){
                ;
            }else{
                in = 1;
                word_count++;
            }
        }
    }
    printf("\nword count is %d\n",word_count);
    return(EXIT_SUCCESS);
}
