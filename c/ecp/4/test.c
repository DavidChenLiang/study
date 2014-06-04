#include <stdio.h>

void 
func1(char ca[])
{
    printf("in func1 ca       is:%p\n",ca);
    printf("in func1 &ca      is:%p\n",&ca);
    printf("in func1 &(ca[0]) is:%p\n",&(ca[0]));
    printf("in func1 &(ca[1]) is:%p\n",&(ca[1]));
    printf("\n");
}

void
func2(char *pa)
{
    printf("in func2 pa       is:%p\n",pa);
    printf("in func2 &pa      is:%p\n",&pa);
    printf("in func2 &(pa[0]) is:%p\n",&(pa[0]));
    printf("in func2 &(pa[1]) is:%p\n",&(pa[1]));
    printf("\n");
} 

int
main(void)
{
    char ca[] = "abcd";
    func1(ca);
    func2(ca);
    char *pa = "abcd";
    printf("in main pa       is:%p\n",pa);
    printf("in main &pa      is:%p\n",&pa);
    printf("in main &(pa[0]) is:%p\n",&(pa[0]));
    printf("in main &(pa[1]) is:%p\n",&(pa[1]));

        
    return 0;
}
