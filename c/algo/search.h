/*
 * =====================================================================================
 *
 *       Filename:  search.h
 *
 *    Description:  search
 *
 *        Version:  1.0
 *        Created:  2015年08月08日 18时01分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef SEARCH_H
#define SEARCH_H
int
bisearch(void *sorted,
         const void *target, 
         int size, 
         int esize, 
         int (*compare)(const void *key1,const void *key2));
#endif
