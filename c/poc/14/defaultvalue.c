#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    printf("source file name: %s\n",__FILE__);
    printf("line is: %d\n",__LINE__);
    printf("date is: %s\n",__DATE__);
    printf("time is: %s\n",__TIME__);
    printf("stdc is: %d\n",__STDC__);
    return EXIT_SUCCESS;
}

