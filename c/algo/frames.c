/*
 * =====================================================================================
 *
 *       Filename:  frame.c
 *
 *    Description:  frame
 *
 *        Version:  1.0
 *        Created:  2015年08月09日 18时19分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>
#include    "frames.h"
#include    "list.h"

int
alloc_frame(List *frames){
    int frame_number,*data;
    if(list_size(frames) == 0)
        return -1;
    else{
        if (list_rem_next(frames,NULL,(void **)&data) != 0)
            return -1;
        else{
            frame_number = *data;
            free(data);
        }
    }
    return frame_number;
}
int
free_frame(List *frames, int frame_number){
    int *data;
    if ((data = (int *)malloc(sizeof(int))) == NULL)
        return -1;
    *data = frame_number;
    if (list_ins_next(frames, NULL,data) != 0)
        return -1;
    return 0;
}
void
destroy(void *data){
    if (data){
        free(data);
    }
    return;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    List * list = (List *)malloc(sizeof(List));
    list_init(list,destroy);

    int *data = (int *)malloc(sizeof(int));
    *data = 10;
    list_ins_next(list,NULL,data);
    
    data = (int *)malloc(sizeof(int));
    *data = 20;
    list_ins_next(list,NULL,data);
    
    ListElmt * tempElmt = list->head;
    int size = list_size(list);
    printf("size: %d\n",size);
    while (size >0){
        int * temp = (int *)(tempElmt->data); 
        fprintf(stdout,"%d\n",*temp);
        tempElmt  = tempElmt->next;
        size--;
    }
    tempElmt = list->head;
    while (tempElmt){
        if (list->destroy){
            list->destroy(tempElmt->data);    
            printf("destroy is not null\n");
        }else{
            printf("destroy is null\n");
            free(tempElmt->data);
        }
        tempElmt = tempElmt->next;
    }

    free(list);
    return EXIT_SUCCESS;

}				/* ----------  end of function main  ---------- */

