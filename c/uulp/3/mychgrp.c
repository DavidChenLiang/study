/*
 * =====================================================================================
 *
 *       Filename:  mychgrp.c
 *
 *    Description:  my change group
 *
 *        Version:  1.0
 *        Created:  2015年07月19日 11时53分33秒
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
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
        int
main ( int argc, char *argv[] )
{       int opt;
        opt = getopt(argc,argv,""); 
        struct group  *grp;
        if ((grp=getgrnam(argv[optind])) != NULL){
                printf("%s\n",grp->gr_name);
        }
        if (chgrp(argv[optind++],grp->gr_gid) == -1){
                perror("mychgrp");
                exit(-1);
        }

        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
