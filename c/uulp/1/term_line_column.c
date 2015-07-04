#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

int main(void){

	struct winsize size;
	ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
	printf("line is %d\n",size.ws_row);
	printf("colu is %d\n",size.ws_col);
	return 0;
}
