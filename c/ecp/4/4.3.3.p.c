#include <stdio.h>

void
func(void)
{
    extern int *a;
    int b = 100;
    a = &b;
    int c = *a;
    printf("c is %d\n",c);
}




int
main(void)
{
    func();
    return 0;
}
