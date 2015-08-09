/*
 * =====================================================================================
 *
 *       Filename:  frame.h
 *
 *    Description:  frame.h 
 *
 *        Version:  1.0
 *        Created:  2015年08月09日 18时21分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef     FRAME_H
#define     FRAME_H
#include "list.h"
int alloc_frame(List *frame);
int free_frame(List *frame, int frame_number);

#endif
