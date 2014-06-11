#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int
main(void)
{
    printf("before my pid is %d\n",getpid());
    fork();
    fork();
    fork();
    printf("after my pid is %d\n",getpid());
    return EXIT_SUCCESS;
}
