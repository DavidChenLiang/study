/*
 * =====================================================================================
 *
 *       Filename:  bisearch.c
 *
 *    Description:  bisearch.c
 *
 *        Version:  1.0
 *        Created:  2015年08月08日 18时03分12秒
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
#include "search.h"
int 
bisearch(void *sorted,
         const void *target,
         int size,
         int esize, 
         int (*compare)(const void *key1, const void *key2)){
        int left,
            middle,
            right;
        left = 0;
        right = size -1;
        while (left <= right){
            middle = (left + right)/2;
            switch(compare(((char *)sorted + (esize * middle)),target)){
                case -1:
                        left = middle + 1;
                        break;
                case 1:
                        right = middle - 1;
                        break;
                case 0:
                        return middle;
            }
        }
        return -1;
}


