#include <stdio.h>
y#include <signal.h>
#include <termios.h>

int
main(void)
{
    void f(int);
    int i;
    tty_mode(0);
    set_cr_noecho_mode();
    signal(SIGINT,f);
    for (i = 0; i<5; i++){
        printf("hello\n");
        sleep(1);
    }
    tty_mode(1);
}

void f(int signum){
    printf("OUCH!\n");
}

set_cr_noecho_mode(){
    struct termios   ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag   &= ~ECHO;
    tcsetattr(0, TCSANOW, &ttystate);
}

tty_mode(int how){
    static struct termios original_mode;
    if (how == 0)
         tcgetattr(0, &original_mode);
    else
        return tcsetattr(0, TCSANOW, &original_mode);
}
