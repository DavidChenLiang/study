/*
 * =====================================================================================
 *
 *       Filename:  sigactdemo.c
 *
 *    Description:  for sig action demo
 *
 *        Version:  1.0
 *        Created:  2015年02月07日 13时21分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#define  INPUTLEN  100

int
main(void)
{
    struct sigaction newhandler;
    sigset_t         blocked;
    void             inthandler();
    char             x[INPUTLEN];
    
    newhandler.sa_handler = inthandler;
    newhandler.sa_flags   = SA_RESETHAND|SA_RESTART;
    sigemptyset(&blocked);
    sigaddset(&blocked, SIGQUIT);
    newhandler.sa_mask = blocked;

    if (sigaction(SIGINT, &newhandler,NULL) == -1)
	perror("sigaction");
    else 
	while(1){
	    fgets(x,INPUTLEN,stdin);
	    printf("input: %s", x);
	}
}
void inthandler(int s)
{
    printf("Called with signal %d\n", s);
    sleep(s);
    printf("Done handling signal %d",s);

}

