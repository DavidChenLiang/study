#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int
main(void)
{
    printf("before my pid is %d,my ppid is %d\n",getpid(),getppid());
    fork();
    fork();
    fork();
    printf("after my pid is %d,my ppid is %d\n",getpid(),getppid());
    return EXIT_SUCCESS;
}
