/*
 * =====================================================================================
 *
 *       Filename:  varlib.h
 *
 *    Description:  for varlib
 *
 *        Version:  1.0
 *        Created:  2015年02月28日 16时51分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

int VLstore(char *,char *);
char * VLlookup(char *);
int VLexport(char *);
void VLlist(void);
char ** VLtable2env(void);
int  VLenv2table(char * env[]);
