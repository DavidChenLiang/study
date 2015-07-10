/*
 * =====================================================================================
 *
 *       Filename:  od.c
 *
 *    Description:  dump files in octal formats 
 *
 *        Version:  1.0
 *        Created:  2015年07月07日 09时57分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  handle arguments
 *        Input:  file which to be dumped
 *       Output:  print octal format to stdout
 * =====================================================================================
 */
int
main ( int argc, char *argv[] )
{
        if (argc == 1){
                printf("Parameter files must not be null.\n");
                exit(-1);
        }
        int fd;
        if ((fd = open(argv[1],O_RDONLY)) == -1)
        {
                perror("Cannot open file");
                return -1;
        }
        char c;
        int newLine = 0;
        printf("%o\t",newLine);
        while (read(fd,&c,1) == 1){
                newLine++;
                if ((newLine % 16) == 0){
                    printf("\n%o\t",newLine);
                }
                printf("%o  ",c);
                fflush(stdout);

        }
        printf ("\n");
//        printf("--%d--\n",count);
        if (close(fd) == -1){
                perror("Cannot close file");
                return -1;
        }
        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
