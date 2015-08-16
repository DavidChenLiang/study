/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  queue.h
 *
 *        Version:  1.0
 *        Created:  2015年08月16日 17时16分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include "list.h"
typedef List Queue;
#define queue_init      list_init
#define queue_destroy   list_destroy
int queue_enqueue(Queue *queue, const void *data);
int queue_dequeue(Queue *queue, void **data);
#define queue_peek(queue) ((queue)->head == NULL ? NULL:(queue)->head->data)
#define queue_size list_size
#endif
