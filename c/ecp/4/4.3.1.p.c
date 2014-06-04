#include <stdio.h>

void
func(void)
{
    extern int a[];
    int c = *a;
    printf("c is %d\n",c);

}



int
main(void)
{
    func();
    return 0;

}
