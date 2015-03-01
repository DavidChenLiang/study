/*
 * =====================================================================================
 *
 *       Filename:  buildin.c
 *
 *    Description:  for build in command
 *
 *        Version:  1.0
 *        Created:  2015年02月28日 11时03分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "smsh.h"
#include "varlib.h"

int okname(char *);
int assign(char *);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  builtin_command
 *  Description:  1 for build in command, 0 for not 
 * =====================================================================================
 */
   int 
builtin_command (char **args, int * resultp)
{
    int rv = 0;
    if (strcmp(args[0],"set") == 0)
    {
	VLlist();
	*resultp = 0;
	rv = 1;
    }else if (strchr(args[0],'=') != NULL)
    {
	*resultp = assign(args[0]);
	if (*resultp != -1)
	    rv =1;
    }else if (strcmp(args[0],"export") == 0)
    {
	if (args[1]!=NULL&&okname(args[1]))
	    *resultp = VLexport(args[1]);
	else
	    *resultp = 1;
	rv = 1;
    }else if (strcmp(args[0],"cd") == 0)
    {
	if (args[1]!= NULL )
	{
	    *resultp = VLstore("PWD",args[1]);
	    rv = 1;
	}

    }

    return rv;
}		/* -----  end of function builtin_command  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  assign
 *  Description: execute name = val And ensure that name is legal 
 * =====================================================================================
 */
    int
assign (char *str)
{
    int rv;
    char * cp;
    cp = strchr(str,'=');
    *cp = '\0';
    rv = okname(str)?VLstore(str,cp+1):-1;
    return rv;
}		/* -----  end of function assign  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  okname
 *  Description:  determine is a str is a legal variable name 
 * =====================================================================================
 */
    int
okname (char *str )
{
    char *cp;

    for (cp = str; *cp; cp++)
    {
	if ((isdigit(*cp)&&cp == str) ||
	    !(isalnum(*cp)||*cp == '_')) 
	return 0;   
    }
    return (cp  != str); /* no empty string is allow */
}		/* -----  end of function okname  ----- */


