#include <stdio.h>
#include <stdlib.h>

int
read_column_numbers(int columns[], int max)
{
    int num = 0;
    int ch;

    while (num < max && scanf("%d", &columns[num]) == 1 && columns[num] >= 0){
            num += 1;
            printf("%d\n",num);
    }

    if (num %2 != 0){
            puts("Last column number is not paired.\n");
	    exit(EXIT_FAILURE);
    }

    while ((ch = getchar()) != EOF && ch != '\n')
	    ;

    return num;
}
