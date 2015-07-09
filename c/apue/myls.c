/*
 * =====================================================================================
 *
 *       Filename:  myls.c
 *
 *    Description:  ls
 *
 *        Version:  1.0
 *        Created:  2015年07月09日 22时07分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "apue.h"
#include <dirent.h>


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
        int
main ( int argc, char *argv[] )
{
        DIR            *dp;
        struct dirent  *dirp; 
        if (argc != 2){
                err_quit("usage: ls directory name");
        }
        if ((dp = opendir(argv[1])) == NULL){
                err_sys("cann't open %s",argv[1]);
        }
        while ((dirp = readdir(dp)) != NULL){
                printf("%s\n",dirp->d_name);
        }
        closedir(dp);
        exit(0);
}				/* ----------  end of function main  ---------- */
