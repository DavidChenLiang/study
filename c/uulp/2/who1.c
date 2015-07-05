#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST

void show_info(struct utmp *utbufp);
int 
main()
{
    struct utmp current_record;
    int         utmpfd;
    int         reclen = sizeof(current_record);
    if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror(UTMP_FILE);
        exit(1);
    }
    printf("Type     Pid      Name     Line     Id       User     Session  Host\n");
    while ( read(utmpfd, &current_record, reclen) == reclen )
       show_info(&current_record);
     
    close(utmpfd);
    return(0) ;
}


void show_info(struct utmp *utbufp)
{
    printf("%-8d ",  utbufp->ut_type);
    printf("%-8d ",  utbufp->ut_pid);
    printf("%-8.8s ",utbufp->ut_name);
    printf("%-8.8s ",utbufp->ut_line);
    printf("%-8.8s ",utbufp->ut_id);
    printf("%-8.8s ",utbufp->ut_user);
    printf("%-8.8d ",utbufp->ut_session);
//    printf("%10ld  ", utbufp->ut_time);
    #ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
    #endif
    printf("\n");



}
