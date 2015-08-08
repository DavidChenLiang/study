/*
 * =====================================================================================
 *
 *       Filename:  ctsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月08日 10时34分56秒
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
#include "sort.h"
int
ctsort(int *data, int size, int k){
        int *counts,
            *temp;
        int i,
            j;
        if ((counts = (int *)malloc(k * sizeof(int))) == NULL)
                return -1;
        if ((temp = (int *)malloc(size * sizeof(int))) == NULL)
                return -1;
        for (i = 0;i < k; i++)
                counts[i] =0;
        for (j = 0; j < size; j++)
                counts[data[j]] = counts[data[j]] + 1;
        for (i = 1; i < k; i++) 
                counts[i] = counts[i] + counts[i - 1];
        for (j  = size -1; j>=0; j--){
                temp[counts[data[j]]-1] = data[j];
                counts[data[j]] = counts[data[j]] - 1;
        }
        memcpy(data,temp, size * sizeof(int));
        free(counts);
        free(temp);
        return 0;
}

