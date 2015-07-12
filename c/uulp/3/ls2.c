
/*-----------------------------------------------------------------------------
 *  
 *-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

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
    DIR * dir_ptr;                              /* dir descriptor */
    struct dirent * direntp;

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls1: Cannot open %s\n", dirname);
    else
     {
         while ((direntp = readdir(dir_ptr)) != NULL)
            printf("%s\n",direntp->d_name);
            if (closedir(dir_ptr)){
                    perror("Can not close dir");
                    exit(0);
            }
     }
}
