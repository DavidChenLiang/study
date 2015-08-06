/*
 * =====================================================================================
 *
 *       Filename:  sort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月06日 22时14分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef SORT_H
#define SORT_H
int issort(void *data,int size, int esize, int (*compare)(const void *key1, const void *key2));
#endif

