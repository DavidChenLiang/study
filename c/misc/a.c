#include <stdio.h>
extern int shared;
extern int never_used;
extern int swap(int *, int *);

int
main(void)
{
    int a = 100;
    printf("a is:%d, shared is:%d\n",a,shared);
    swap(&a,&shared);
    printf("a is:%d, shared is:%d\n",a,shared);
    return 0;
}
