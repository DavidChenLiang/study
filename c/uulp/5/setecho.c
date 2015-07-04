#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

#define oops(s,x) {perror(s);exit(x);}
int
main(int ac, char *args[])
{
    struct termios info;
    if (ac == 1) exit(0);
    if (tcgetattr(0, &info)==-1)
	    oops("tcgetattr",1);
    if (args[1][0] == 'y'){
        info.c_lflag |= ECHO;
    } else {
        info.c_lflag &= ~ECHO; 
    }

    if (tcsetattr(0,TCSANOW,&info) == -1){
        oops("tcgetattr",2);
    }
}
