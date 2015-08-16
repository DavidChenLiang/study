/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  stack.h
 *
 *        Version:  1.0
 *        Created:  2015年08月16日 16时58分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include "list.h"
typedef List Stack;
#define stack_init      list_init
#define stack_destroy   list_destroy
int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);

#define stack_peek() ((stack)->head == NULL ? NULL: (stack)->head->data)
#define stack_size list_size
#endif
