/*
 * =====================================================================================
 *
 *       Filename:  CString.c
 *
 *    Description:  CString implementation
 *
 *        Version:  1.0
 *        Created:  01/31/2015 02:22:30 PM
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

typedef struct{
    char *str;
    int  len;
} CString;

CString *Init_CString(char *str)
{
    CString *p = malloc(sizeof(CString));
    p->len = strlen(str);
    p->str = malloc(p->len + 1);
    strncpy(p->str, str, strlen(str)+1);
    return p;
}

void Delete_CString(CString *p)
{
    free(p->str);
    free(p);
}

//Revomes the last character of a CString and returns it.
//
char chmop(CString *cstring)
{
    char lastchar = *(cstring->str + cstring->len - 1);
    //shorten the string by one
    *(cstring->str + cstring->len - 1) = '\0';
    cstring->len = strlen(cstring->str);

    return lastchar;
}
// Appends a char * to a CString
//
CString *Append_Chars_To_CString(CString *p, char *str)
{
    char *newstr = malloc(p->len + 1);
    p->len = p->len + strlen(str);
    //Create the new string to replace p->str
    snprintf(newstr, p->len + 1, "%s%s",p->str, str);
    //Free old string and make CString pointto the new string
    free(p->str);
    p->str = newstr;
    return p;

}
int main(void)
{
    CString *mystr;
    char c;

    mystr = Init_CString("Hello!");
    printf("Init:\n str: '%s' len: %d\n",mystr->str,mystr->len);

    c = chmop(mystr);

    printf("Chmop '%c':\n str:'%s' len: %d\n",c,mystr->str,mystr->len );
    mystr = Append_Chars_To_CString(mystr, " world!");
    printf("Append:\n str:'%s' len: %d\n",mystr->str,mystr->len );
    Delete_CString(mystr);
    return 0;
}
