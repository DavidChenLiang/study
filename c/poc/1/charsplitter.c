#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charsplitter.h"



int
main(void)
{
    int   n_columns;
    int   columns[MAX_COLS];
    char  input[MAX_INPUT];
    char  output[MAX_INPUT];


    n_columns = read_column_numbers(columns, MAX_COLS);
    while (gets(input) != NULL){
        printf("Original input : %s \n", input);
	rearrange(output, input,n_columns, columns);
	printf("Rearrange line : %s\n", output);
    }
    return 0;


}

