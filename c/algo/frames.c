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
    list_init(list,NULL);
    int *data = (int *)malloc(sizeof(int));
    *data = 10;
    list_ins_next(list,NULL,data);
    free(list);
    return EXIT_SUCCESS;

}				/* ----------  end of function main  ---------- */

