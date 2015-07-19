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
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parse
 *  Description:  
 * =====================================================================================
 */
        int
mychown (char * idString ,char * path)
{
        int retval = -1;
        char  delimiter = ':';
        int i = 0;
        if (strchr(idString, delimiter) != NULL){
           while (idString[i++] != ':') {
                ;
           }
        }
//        printf("i = %d\n",i);
        char uid[256];
        int index = 0;
        for (;index<i-1;index++){
            uid[index] = idString[index];
        }
        uid[index] = '\0';
//        printf("%s\n",uid); 
        index =0;
        char gid[256];
        int idStrLen = strlen(idString);
        for (;(index+i)<idStrLen;index++) {
            gid[index] = idString[index+i];
        }
        gid[index] = '\0';
//        printf("%s\n",gid);
        struct passwd  *pwd; 
        if ( (pwd = getpwnam(uid)) != NULL){
            printf("%s\n",pwd->pw_name);
        }
        struct group *grp;
        if ((grp= getgrnam(gid)) != NULL){
            printf("%s\n",grp->gr_name);
             }
        if (chown(path, pwd->pw_uid,grp->gr_gid)){
            perror("chown");
            exit(EXIT_FAILURE);
        }

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
        if (mychown(argv[optind],argv[optind+1])){

        }
     
        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

