#include <stdlib.h>
#include "display.h"
int
main(void)
 {
     char * str ="Hello Cursor\n";
     Display_Message(10,10,str);
     //Display_Cursor();
     //Hide_Cursor();
     //Clear_All_Display();
     //Clear_Screen();
     //Display_Message(24,20,str);
     //Move_Cursor(40,20);
     Draw_Box(20,40,10,20);
     return EXIT_SUCCESS;
 }

