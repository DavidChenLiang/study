/*
 * =====================================================================================
 *
 *       Filename:  mydu.c
 *
 *    Description:  my disk usage
 *
 *        Version:  1.0
 *        Created:  2015年07月20日 21时53分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include	<stdlib.h>
#include <unistd.h>
#include <stdio.h>
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

        getopt(argc,argv,"h");
        printf("%s\n",argv[optind]);
        
        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
