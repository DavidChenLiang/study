/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  queue.c
 *
 *        Version:  1.0
 *        Created:  2015年08月16日 17时21分04秒
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
#include "queue.h"
int
queue_enqueue(Queue *queue, const void *data){
    return list_int_next(queue, list_tail(queue),data);
}
int
queue_dequeue(Queue *queue, void **data){
    return list_rem_next(queue,NULL,data);
}
