#include <stdio.h>
#include <stdlib.h>

int
main()
{
    char *string = "Blunder??!??\n";    
    printf("%s",string);

    printf("%%d %d\n",40);
    printf("%%o %o\n",40);
    printf("%%x %x\n",40);
    printf("%%c %c\n",40);
    printf("%%g %g\n",40.00);
    printf("================");
    printf("\n");
    printf("%%d %d\n",100);
    printf("%%o %o\n",100);
    printf("%%x %x\n",100);
    printf("%%c %c\n",100);
    printf("%%g %g\n",100.0);
    printf("================");
    printf("\n");
    printf("%%d of 0x40:%d\n",0x40);
    printf("%%o of 0x40:%o\n",0x40);
    printf("%%x of 0x40:%x\n",0x40);
    printf("%%c of 0x40:%c\n",0x40);
   // printf("%%g of 0x40:%g\n",0x40.0);
    printf("================");
    printf("\n");
    printf("%%d of 0123:%d\n",0123);
    printf("%%o of 0123:%o\n",0123);
    printf("%%x of 0123:%x\n",0123);
    printf("%%c of 0123:%c\n",0123);
    printf("================");
    printf("\n");
    int x/*blah*/,y;
    return(EXIT_SUCCESS);
}
