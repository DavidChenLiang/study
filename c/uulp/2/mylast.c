/*
 * =====================================================================================
 *
 *       Filename:  mylast.c
 *
 *    Description:  head
 *
 *        Version:  1.0
 *        Created:  2015年07月10日 15时03分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
        int
main ( int argc, char *argv[] )
{
        int opt;
        int displayCounter = 10;                /* default print 10 lines of file */
        while ((opt = getopt(argc,argv,"n:")) != -1){ /* scan all the options until met a argumnt */
                switch(opt){
                        case('n'):
                                displayCounter = atoi(optarg);
                                break;
                }
        }
        printf("argc =%d\n",argc);
        printf("optind =%d\n",optind);
        printf("argvNumber =%d\n",argc - optind);
        printf("=================\n");
        int fd;
        if ((fd = open("/var/log/wtmp",O_RDONLY)) == -1){
            perror("Can not open file");
            exit(1);
        }
        struct utmp * utmpBuf; 
        utmpBuf = malloc(sizeof(struct utmp)); 
        int count = 1;
        while(count <= displayCounter){
            lseek(fd,-(sizeof(struct utmp)*count),SEEK_END);
            read(fd,utmpBuf,sizeof(struct utmp)); 
            if (utmpBuf->ut_type != USER_PROCESS) {
                    count++;
                    continue;
            }
            printf("%-8.8s",utmpBuf->ut_name);
            printf("%-8.8s",utmpBuf->ut_line);
            printf("%12.12s\n",ctime(&(utmpBuf->ut_time))); 
            count++;
        }
        if (close(fd) == -1){
            perror("Can not close file");
        }
        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
