/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  stack.c
 *
 *        Version:  1.0
 *        Created:  2015年08月16日 17时13分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "list.h"
#include "stack.h"
int
stack_push(Stack *stack, const void *data){
    return list_ins_next(stack,NULL,data);
}
int
stack_pop(Stack *stack,void **data){
    return list_rem_next(stack,NULL,data);
}
