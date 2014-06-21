#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
int
main()
{
    struct termios ttyinfo;
    if (tcgetattr(STDIN_FILENO, &ttyinfo) == -1){
        perror("cannot get params about stdin");
        exit(1);
    }
    return EXIT_SUCCESS;
}
