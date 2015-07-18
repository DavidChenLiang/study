/*
 * =====================================================================================
 *
 *       Filename:  myfile.c
 *
 *    Description:  myfile.c
 *
 *        Version:  1.0
 *        Created:  2015年07月14日 20时12分02秒
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
#include <sys/stat.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  do_magic
 *  Description:  
 * =====================================================================================
 */
        void
do_magic ( char * filename)
{

}		/* -----  end of function do_magic  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  do_language
 *  Description:  
 * =====================================================================================
 */
        void
        
do_language ( char * filename)
{
}		/* -----  end of function do_language  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  do_stat
 *  Description:  
 * =====================================================================================
 */
        void
do_stat ( char * filename )
{
        struct stat bufp ;
        if (stat(filename,&bufp) != -1){
            if (S_ISREG(bufp.st_mode)){
                printf("%s : reg\n",filename);
                }
            if (S_ISDIR(bufp.st_mode)){
                printf("%s : dir\n",filename);
            }
            if (S_ISCHR(bufp.st_mode)){
                printf("%s : chr\n",filename);
            } 
            if (S_ISBLK(bufp.st_mode)){
                printf("%s : blk\n",filename);
            }
            if (S_ISFIFO(bufp.st_mode)){
                printf("%s : fifo\n",filename);
            }
            if (S_ISLNK(bufp.st_mode)){
                printf("%s : link\n",filename);
            }
            if (S_ISSOCK(bufp.st_mode)){
                printf("%s : sock\n",filename);
            }
        }

}		/* -----  end of function do_stat  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
        int
main ( int argc, char *argv[] )
{
        if (argc == 1){
            perror("Please input at least one file name.");
            exit(0);
        }
        int i = 1;
        if (argc - i){
            do_stat(argv[i++]);            
            do_magic(argv[i++]);
            do_language(argv[i++]);
        }

        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
