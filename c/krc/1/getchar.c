#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    char c;
    while((c = getchar()) != EOF){
        putchar(c);
    }

    return(EXIT_SUCCESS);
}
