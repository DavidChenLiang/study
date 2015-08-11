/*
 * =====================================================================================
 *
 *       Filename:  issort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月06日 22时34分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"
int
issort(void *data, int size, int esize,int (*compare)(const void *key1,
                        const void *key2)){
        
        extern int b;
        b = 2;
        printf("%d\n",b);
        char *a = data;
        void *key;
        int i,
            j;
        if ((key = (char *)malloc(esize)) == NULL)
                return -1;
        for (j = 1; j<size; j++){
                memcpy(key, &a[j * esize], esize);
                i = j - 1;
                while (i >= 0 && compare(&a[i * esize],key) > 0){
                        memcpy(&a[(i+1) * esize], &a[i*esize],esize);
                        i--;
                }
                memcpy(&a[(i+1)* esize], key, esize);
        }
        free(key);
        return 0;
}
