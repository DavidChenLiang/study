#include <stdio.h>
#include <stdlib.h>
int fibonacci(int n);

int 
main(void)
{
    printf("Fibonacci(3) is %d.\n", fibonacci(3));
   
    return EXIT_SUCCESS;
}

int fibonacci(int n)
{
    if (n <= 0 || n ==1){
        return 1;
    }else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}
