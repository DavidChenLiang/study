/*
 * =====================================================================================
 *
 *       Filename:  cp1.c
 *
 *    Description:  just copy
 *
 *        Version:  1.0
 *        Created:  2015年02月09日 20时54分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFERSIZE    4096
#define COPYMODE      0644

void oops(char *,char *);

int
main(int argc, char *argv[])
{
    int    in_fd,out_fd, n_chars;
    char   buf[BUFFERSIZE];
    if (argc !=3){
	fprintf(stderr,"usage: %s source destination\n",*argv);
	exit(EXIT_FAILURE);
    }

    if ((in_fd = open(argv[1],O_RDONLY)) == -1)
	oops("Cannot open ", argv[1]);
    if ((out_fd = create(argv[2],COPYMODE)) == -1)
	oops("Cannot create ", argv[2]);

    while ((n_chars = read(in_fd,buf,BUFFERSIZE)) >0)
	if (write(out_fd,buf,n_chars) != n_chars)
	    oops("Write error to ", argv[2]);
    if (n_chars == -1)
	oops("Error closing files ","");

}
void oops(char * s1,char * s2)
{
    fprintf(stderr, "Error: %s",s1);
    perror(s2);
    exit(EXIT_FAILURE);
	
}

