/*
 * =====================================================================================
 *
 *       Filename:  directls.h
 *
 *    Description:  directls
 *
 *        Version:  1.0
 *        Created:  2015年08月07日 22时40分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef DIRECT_H
#define DIRECT_H
#include <dirent.h>
typedef struct Directory_{
        char    name[MAXNAMLEN + 1];
}Directory;
int directory(const char *path, Directory **dir);
#endif
