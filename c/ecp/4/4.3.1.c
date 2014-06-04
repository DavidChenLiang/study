#include <stdio.h>

void
func(void)
{
    extern int a[];
    int c = a[0];
    printf("c is %d\n",c);

}



int
main(void)
{
    func();
    return 0;

}
