/************************************************************
    FileName : display.c 
    FileFunc : 控制屏幕显示信息和光标的状态实现文件    
    Version  : V0.1     
    Author   : Sunrier     
    Date     : 2012-06-09 
    Descp    : Linux下实现屏幕和光标的控制     
*************************************************************/  
#include <stdlib.h>
#include "display.h"  
  
//x->行(从1开始),y->列(从1开始)  
//在X行Y列显示信息  
void Display_Message(int x,int y,char *str)  
{  
    unsigned int uiLen=0;  
    char szMessage[512];  
    memset(szMessage,0,sizeof(szMessage));  
  
    sprintf(szMessage,"\033[%d;%dH%s",x,y,str);  
    uiLen = strlen(szMessage);  
    write(1,szMessage,uiLen);  
}  
  
//画边框  
void Draw_Box(int row,int col,int len,int wid)  
{  
    int i = 0,end = 0;  
    char szTop[100],szBottom[100];  
  
    memset(szTop,0,sizeof(szTop));  
    memset(szBottom,0,sizeof(szBottom));  
    strcpy(szTop,"┏");  
    strcpy(szBottom,"┗");  
    for (i=1;i<wid/2-1;i++)  
    {  
        strcat(szTop,"━");  
        strcat(szBottom,"━");  
    }  
    strcat(szTop,"┓\0");  
    strcat(szBottom,"┛\0");  
  
    end=col+wid/2*2-2;  
    Display_Message(row,col,szTop);  
    for (i=1;i<len-1;i++)   
    {  
        Display_Message(row+i,col,"┃");  
        Display_Message(row+i,end,"┃\0");  
    }  
    Display_Message(row+len-1,col,szBottom);
}  
  
//移动光标到X行Y列  
void Move_Cursor(int x,int y)  
{  
    unsigned int uiLen = 0;  
    char szMessage[16];  
  
    memset(szMessage,0,sizeof(szMessage));  
    sprintf(szMessage,"\033[%d;%dH",x,y);  
    uiLen=strlen(szMessage);  
    write(1,szMessage,uiLen);  
}  
  
//显示光标  
void Display_Cursor( void )  
{  
    printf("\033[?25h");  
}  
  
//隐藏光标  
void Hide_Cursor( void )  
{  
    printf("\033[?25l");  
}  
  
//清除所有的显示信息(X:1到25行;Y:1到80列)  
void Clear_All_Display( void )  
{  
    int i=0;  
    char  szZero[MAX_DISPLAY_WIDTH];  
    memset(szZero, ' ', sizeof(szZero));  
    szZero[sizeof(szZero) -1] = 0;  
    for(i = 1; i <= MAX_DISPLAY_ITEM; i++)  
    {  
        Display_Message(i,1,szZero);  
    }  
}  
  
//清除屏幕  
void Clear_Screen( void )  
{  
    //printf("\033[2J\033[1;1H\n");  
    printf("\033[2J\033[1;1H");  
}

