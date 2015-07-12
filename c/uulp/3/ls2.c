
/*-----------------------------------------------------------------------------
 *  
 *-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  strcmpgp
 *  Description:  
 * =====================================================================================
 */
        static int
strcmpgp ( const void * p1, const void * p2)
{
        return strcmp(*(char * const *)p1,*(char * const *)p2);
}		/* -----  end of static function strcmpgp  ----- */
void do_ls(char[]);

int
main(int ac, char *av[]){
    int opt;
    int longfnd;
    int hiddenfnd;
    while (opt = getopt(ac,av,"la") !=-1){
        switch(opt){
            case 'l':
                    longfnd = 1;
                    break;
            case 'a':
                    hiddenfnd = 1;
                    break;
            }
    }
    if (ac == 1) 
        do_ls(".");
    else
        while (optind < ac){
            printf("%s:\n", av[optind]);
            do_ls(av[optind]);
            optind++;
        }
        
}

void do_ls(char dirname[]){
    DIR * dir_ptr;                              /* DIR is dir descriptor */
    struct dirent * direntp;

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls1: Cannot open %s\n", dirname);
    else
     {
         char * * dirBuf;
         int dirBufIndex = 0;
         while ((direntp = readdir(dir_ptr)) != NULL){
            dirBuf[dirBufIndex] = malloc(sizeof(strlen(direntp->d_name) + 1)); /* malloc for each dir entry */
            strcpy(dirBuf[dirBufIndex++],direntp->d_name + '\0'); /*  make sure the entry is put*/
            
         }  
         if (closedir(dir_ptr)){                /* try to close the DIR */
                    perror("Can not close dir");
                    exit(0);
            }                                    /* end of while */
         qsort(dirBuf,dirBufIndex,sizeof(char *),strcmpgp);                /* sort thr buf u*/
         int i = 0;
         while (dirBuf[i] != NULL){
                printf("%s\n",dirBuf[i++]);
         }
     }
}
