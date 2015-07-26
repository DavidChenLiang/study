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
#include <sys/stat.h>
#include <sys/types.h>

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
        while (opt = getopt(argc,argv,"h") != -1){
            switch(opt){
            case 'h':
                ;
            }

        }
        struct stat statbuf;
        if (stat(argv[optind],&statbuf) == -1){
            perror("Can not stat");
            exit(-1);
        }
        int count =0;
        if (S_ISDIR(statbuf.st_mode)){
                DIR * dir_ptr;
                struct dirent * direntp;
                if ((dir_ptr = opendir(argv[optind])) == NULL){
                        fprintf(stderr,"can not open dir %s\n",argv[optind]);
                }else{
                        while ((direntp = readdir(dir_ptr)) != NULL){
//                                printf("%s\n",direntp->d_name);
                                if (stat(direntp->d_name,&statbuf) != -1){
                                if (strcmp(direntp->d_name,".") != 0)
                                    count += (unsigned long long)(statbuf.st_blocks*512)/1024;
//                                    fprintf(stdout,"%lld\t%s\n",(unsigned long long)(statbuf.st_blocks*512)/1024,argv[optind]);
                                }
                        }
                        printf("%d\n ",count);
                        closedir(dir_ptr);
                }
            }else{
        printf("%lld\t%s\n",(unsigned long long)(statbuf.st_blocks*512)/1024,argv[optind]);
            } 
        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
