/*
 * =====================================================================================
 *
 *       Filename:  spell.c
 *
 *    Description:  spell
 *
 *        Version:  1.0
 *        Created:  2015年08月08日 18时14分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "search.h"
#include "spell.h"
static int
compare_str(const void *str1, const void *str2){
        int    retval;
        if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0)
                return 1;
        else if (retval < 0)        
                return -1;
        else
                return 0;
}
int
spell(char (*dictionary)[SPELL_SIZE],
      int size, 
      const char *word){
        if (bisearch(dictionary, word, size, SPELL_SIZE,compare_str) >= 0)
                return 1;
        else 
                return 0;
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
        char dic[][SPELL_SIZE] = {{"ab"},{"cd"}};
        int ret = spell(dic,2,argv[1]);
        if(ret){
                fprintf(stdout, "found %s\n",argv[1]);
        }else{
                fprintf(stdout, "didn't found match\n");
        }
        return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
