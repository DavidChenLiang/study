/*
 * =====================================================================================
 *
 *       Filename:  directls.c
 *
 *    Description:  directls
 *
 *        Version:  1.0
 *        Created:  2015年08月07日 22时42分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directls.h"
#include "sort.h"
extern int b =3;
static int
compare_dir(const void *key1, const void *key2){
       int      retval; 
       if ((retval = strcmp(((const Directory*)key1)->name,((const Directory*)key2)->name)) > 0)
           return 1;
       else if (retval < 0)
           return -1;
       else
           return 0;
}

int
directls(const char *path, Directory **dir){
        DIR             *dirptr;
        Directory       *temp;
        struct dirent   *curdir;
        int             count;
        if ((dirptr = opendir(path)) == NULL)
                return -1;
        *dir  = NULL;
        count = 0;
        while((curdir = readdir(dirptr)) != NULL){
                count++;
                if ((temp = (Directory *)realloc(*dir, count * sizeof(Directory))) == NULL){
                    free(*dir);
                    return -1;
                }
                else{
                    *dir = temp;
                }
                strcpy(((*dir)[count -1]).name,curdir->d_name);
        }
        closedir(dirptr);
#ifdef QK
        if (qksort(*dir, count, sizeof(Directory),0, count -1, compare_dir)!= 0)
                return -1;
#elif IS
        if (issort(*dir,count, sizeof(Directory),compare_dir) != 0) 
                return -1;
#endif
        return count;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
        int
main ( int argc, char *argv[] )
{
        Directory * dir;
        const char path[10] = ".";
        int count  = directls(path, &dir);
#ifdef DEBUG
        fprintf(stdout,"count %d\n",count);
#endif
        if (count > 0)
        { 
            int i;
            for (i=0 ;i < count; i++ )
            fprintf(stdout,"%s\n",dir[i].name);
        }

        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
