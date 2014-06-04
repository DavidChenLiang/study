#include <stdio.h>

int
main(void)
{
    int y = 2; 
    int x = 1;
    int  *p = &x;
    
    y = x /(*p);
    printf("y = x/*p is: %d\n", y);
    printf("n\n");
    
    int a = 1;
    int b = 1;
    //printf("%d\n",(((a++)++)+b));

    int *q;
    printf(q);
    return 0;
}
