#include <stdio.h>
#include <stdlib.h>

void mystery(int n)
{
    n += 5;
    n /=10;
    printf("%s\n","**********"+10-n);
}

int
main(int argc, char **argv)
{   
    int n = 0;
    n = atoi(argv[1]);
    mystery(n);
    return EXIT_SUCCESS;
}
