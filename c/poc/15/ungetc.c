#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int
main(void)
{
    int value = read_int();
    printf("value is %d\n",value);
    return(EXIT_SUCCESS);
}

int
read_int(void)
{
    int value;
    int ch;
    
    value = 0;
    
    while ((ch = getchar()) != EOF && isdigit(ch)){
        value  *= 10;
        value  += ch - '0';
    }
    
    ungetc(ch, stdin);
    return value;
}
