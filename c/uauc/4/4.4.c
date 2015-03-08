/*
 * =====================================================================================
 *
 *       Filename:  4.4.c
 *
 *    Description:  for relalloc 
 *
 *        Version:  1.0
 *        Created:  2015年03月08日 17时03分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getLine
 *  Description:  
 * =====================================================================================
 */
char *
getLine (void)
{
    const size_t sizeIncrement  = 10;
    char * buffer = malloc(sizeIncrement);
    char * currentPosition = buffer;
    size_t maximumLength = sizeIncrement;
    size_t length = 0;
    int character;

    if (currentPosition == NULL) {return NULL;}
    
    while(1)
    {
	character = fgetc(stdin);
	if (character == '\n'){break;}
	if (++length >= maximumLength)
	{
	    char *newBuffer = (char *)realloc(buffer, maximumLength += sizeIncrement);
	    if (newBuffer == NULL)
	    {
		free(buffer);
		return NULL;
	    }
	    currentPosition = newBuffer + (currentPosition - buffer);
	    buffer = newBuffer;
	}
	*currentPosition = '\0'; 
	return buffer;
    }
}		/* -----  end of function getLine  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  trim
 *  Description:  
 * =====================================================================================
 */
char *
trim ( char *phrase)
{
    char *old = phrase;
    char *new = phrase;

    while (*old== ' ')
	old++;
	
    while (*old)
	*(new++) = *(old++);
    *new = '\0';
    return (char *)realloc(phrase, strlen(phrase)+1);
}		/* -----  end of function trim  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    getLine();
    char *buffer = (char *)malloc(strlen("   cat")+1);
    strcpy(buffer, "   cat");
    printf("%s\n",trim(buffer));
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
