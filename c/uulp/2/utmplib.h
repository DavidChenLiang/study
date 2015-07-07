/*
 * =====================================================================================
 *
 *       Filename:  utmplib.h
 *
 *    Description:  Chen Liang

 *        Version:  1.0
 *        Created:  2015年07月06日 14时40分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  UTMPLIB_INC
#define  UTMPLIB_INC
int utmp_open(char * filename);
struct utmp * utmp_next();
void utmp_close();
#endif   /* ----- #ifndef utmplib_INC  ----- */

