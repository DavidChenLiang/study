/*
 * =====================================================================================
 *
 *       Filename:  chtbl.h
 *
 *    Description:  chtbl.h
 *
 *        Version:  1.0
 *        Created:  2015年08月16日 21时04分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CHTBL_H
#define CHTBL_H
#include <stdlib.h>
#include "list.h"
typedef struct CHTbl_{
    int     buckets;
    int     (*h)(const void *key);
    int     (*match)(const void *key1, const void *key2):
    void    (*destroy)(void *data);

    int     size;
    List    *table;
}CHTbl;

int chtbl_init(CHTbl *htbl,int buckets, int (*h)(const void *key),
            int (*match)(const void *key1, const void *key2),
            int (*destroy)(void *data));

void chtbl_destroy(CHTbl *htbl);
int  chtbl_insert(CHTbl *htbl, const void *data);
int  chtbl_remove(CHTbl *htbl, void **data);
int  chtbl_lookup(const CHTbl *htbl, void **data);
#define chtbl_size(htbl) ((html)->size)

#endif
