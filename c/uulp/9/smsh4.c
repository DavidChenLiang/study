#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "smsh.h"
#include "varlib.h"

#define  DFL_PROMPT ">>"

int
main(void)
{
    char    * cmdline, * prompt, ** arglist;
    int     result, process(char **);
    void    setup();
   
    prompt  = DFL_PROMPT;
    setup();
    
    while((cmdline = next_cmd(prompt,stdin)) != NULL){
        if ((arglist = splitline(cmdline)) != NULL){
            result = process(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }
    return result;
}

void setup(){
    extern char ** environ;
    VLenv2table(environ);
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
}

void fatal(char * s1, char * s2, int n){
    fprintf(stderr,"Error: %s, %s\n", s1,s2);
    exit(n);
}
