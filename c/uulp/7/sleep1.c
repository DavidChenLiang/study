#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void wakeup(int);
int
main(void)
{
    printf("about to sleep for 4 senconds.\n");
    signal(SIGALRM,wakeup);
    alarm(4);
    pause();
    printf("Morning so soon?\n");
    return 0;
}

void
wakeup(int signum)
{
    #ifndef SHHHH
        printf("Alarm received from kernel.\n");
    #endif
}
