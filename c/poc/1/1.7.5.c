#include <stdio.h>

int
main(void)
{
    int quanlity, price;
    char string[20];
    printf("please input quality:");
    scanf("%d",&quanlity);
    printf("please input price:");
    scanf("%d",&price);
    printf("please input string:");
    scanf("%s",string);
    printf("quanlity is %d:\n",quanlity);
    printf("price is %d:\n",price);
    printf("string is: %s\n",string);
    return 0;
    
}
