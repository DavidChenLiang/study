/*
 * =====================================================================================
 *
 *       Filename:  sigdemo3.c
 *
 *    Description:  foe sig demo
 *
 *        Version:  1.0
 *        Created:  2015年02月07日 10时40分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define INPUTNUM 100

int
main(int argc, char * argv[])
{
    void inthandler(int);
    void quithandler(int);
    char input[INPUTNUM];
    int  nchars;

    signal(SIGINT, inthandler);
    signal(SIGQUIT, quithandler);

    do{
	printf("\nType a message\n");
	nchars = read(0, input, (INPUTNUM - 1));
	if (nchars == -1)
	    perror("read returned an error");
	else {
	    input[nchars] = '\0';
	    printf("You typed: %s",input);
	    
	}
    }
    while (strncmp(input, "quit",4) != 0);

}

void inthandler(int s)
{
    printf("\nReceived signal %d .. waiting\n",s);
    sleep(2);
    printf("\nLeaving inthandler \n");
}
void quithandler(int s)
{
    printf("\nReceived signal %d .. waiting\n",s);
    sleep(3);
    printf("\nLeaving quithandler \n");
}

