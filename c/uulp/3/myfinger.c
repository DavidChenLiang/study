/*
 * =====================================================================================
 *
 *       Filename:  myfinger.c
 *
 *    Description:  simulate finger
 *
 *        Version:  1.0
 *        Created:  2015年07月18日 17时21分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include <stdio.h>
#include <utmp.h>


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
        int
main ( int argc, char *argv[] )
{
        printf("Login   Name    Tty Idle    Login Time  Office  Office phone\n");
        struct utmp * utmpent  = malloc(sizeof(struct utmp));
        while ((utmpent  = getutent()) != NULL){
            printf("%s  %s  %s  %d\n",utmpent->ut_user,
                              utmpent->ut_user,                           
                              utmpent->ut_line,
                              utmpent->ut_time
                              );        
        }
        free(utmpent);
        return EXIT_SUCCESS;

}				/* ----------  end of function main  ---------- */
