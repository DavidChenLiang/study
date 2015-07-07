#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include "utmplib.h"
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define SHOWHOST

void show_info(struct utmp *utbfup);
int 
main(void)
{
    struct utmp * utbufp;

    if (utmp_open(UTMP_FILE) == -1){
            perror(UTMP_FILE);
            exit(1);
    }
    while ((utbufp = utmp_next()) != ((struct utmp *)NULL))
            show_info(utbufp);
    utmp_close();
    return(0) ;
}

void showtime(long timeval);
void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s ",utbufp->ut_name);
    printf("%-8.8s ",utbufp->ut_line);
    printf("%-8.8s ",utbufp->ut_id);
    showtime(utbufp->ut_time);
    #ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
    #endif
    printf("\n");

}

void showtime(long timeval){
    char * cp;
    cp = ctime(&timeval);
    printf("%12.12s",cp);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  logout_tty
 *  Description:  logout from the specified tty
 * =====================================================================================
 */
int
logout_tty ( char * line)
{
        int retval=-1;
        int fd;
        struct utmp rec;
        int len =sizeof(struct utmp);
        if ((fd = open(UTMP_FILE, O_RDWR)) == -1)
                return -1;
        while (read(fd,&rec,len)== len)
                if (strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == len){
                        rec.ut_type = DEAD_PROCESS;
                        if (time(&rec.ut_time != -1))
                                if (lseek(fd, -len, SEEK_CUR) != -1)
                                    if (write(fd, &rec, len ) == len)
                                        retval = 0;
                        break;
                }
        if (close(fd) == -1)
                retval = -1;
        return retval;
}		/* -----  end of function logout_tty  ----- */
