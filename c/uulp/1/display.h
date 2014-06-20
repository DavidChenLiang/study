/************************************************************
    FileName : display.h 
    FileFunc : 控制屏幕显示信息和光标的状态头文件   
    Version  : V0.1     
    Author   : Sunrier     
    Date     : 2012-06-09 
    Descp    : Linux下实现屏幕和光标的控制     
*************************************************************/  
#ifndef   _DISPLAY_H_      
#define   _DISPLAY_H_   
  
#ifdef __cplusplus  
extern "C" {  
#endif  
  
#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
  
#define MAX_DISPLAY_ITEM    25  //25行  
#define MAX_DISPLAY_WIDTH   80  //80列  
  
void Display_Message(int x,int y,char *str);  
void Draw_Box(int row,int col,int len,int wid);  
void Move_Cursor(int x,int y);  
void Display_Cursor( void );  
void Hide_Cursor( void );  
void Clear_All_Display( void );  
void Clear_Screen( void );  
  
#ifdef __cplusplus  
}  
#endif  
  
#endif   
