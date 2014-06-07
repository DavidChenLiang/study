#include <stdio.h>
int (*fptr1)(int);
int square(int);
main(void)
{
    int n = 5;
    fptr1 = square;
    printf("%d squared is %d\n",n,fptr1(n));
    return 1;
}
int square(int num){
    return num*num;
}
