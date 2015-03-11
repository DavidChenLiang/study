/*
 * =====================================================================================
 *
 *       Filename:  pipedemo2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月10日 14时06分23秒
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
#include <string.h>
#define CHILD_MESS "I want a cokkie\n"
#define PAR_MESS   "testing..."
#define oops(m,x)  {perror(m);exit(x);}
int
main()
{
    int pipefd[2];
    int len;
    char buf[BUFSIZ];
    int read_len;
    
    if (pipe(pipefd) == -1){
	oops("cannot get a pipe",1);
    }
    switch(fork()){
	case -1:
	     oops("cannot get a pipe",1);
	case 0:
	     len = strlen(CHILD_MESS);
	     while (1){
		 if (write(pipefd[1],CHILD_MESS,len)!=0)
		     oops("write",3);
		 sleep(5);
	     }
	default:
	     len = strlen(PAR_MESS);
	     while (1){
		 if (write(pipefd[1],PAR_MESS,len)!=len)
		     oops("write",4);
		 sleep(1);
		 read_len = read(pipefd[0],buf,BUFSIZ);
		 if (read_len <= 0)
		     break;
		 write(1,buf,read_len);
	     }
    }
    return 0;
}


