/*
 * =====================================================================================
 *
 *       Filename:  mychown.c
 *
 *    Description:  chang owner of uid or gid
 *
 *        Version:  1.0
 *        Created:  2015年07月18日 21时41分45秒
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
#include <string.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parse
 *  Description:  
 * =====================================================================================
 */
        int
parse (char * idString )
{
        int retval = -1;
        char  * delimiter = ":";
        printf("%s\n",strtok(idString, delimiter));
        return retval;
}		/* -----  end of function parse  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
        int
main ( int argc, char *argv[] )
{
        if (argc == 1) {
            perror("args can not be blank");
            exit(-1);
        }
        int opt;
        while (opt = getopt(argc,argv,"la") !=-1){
        switch(opt){
            case 'l':;
            }
        }
        if (parse(argv[optind])){

        }
     
        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

