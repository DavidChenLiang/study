#include <string.h>
#include "charsplitter.h"
void
rearrange( char *output, char const *input,
		int n_columns, int const columns[])
{
    int col;
    int output_col;
    int len;

    len = strlen(input);
    output_col = 0;

    for(col = 0; col < n_columns; col += 2){
        int nchars = columns[col + 1] - columns[col] +1;

	if (columns[col] >= len || output_col == MAX_INPUT - 1)
		break;

	if (output_col + nchars > MAX_INPUT - 1){
	    nchars = MAX_INPUT - output_col - 1;
	}

	strncpy(output + output_col, input + columns[col], nchars);
	output_col += nchars;
	output[output_col] = '\0';
    }

}
