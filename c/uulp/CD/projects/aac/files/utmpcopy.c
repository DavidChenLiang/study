/* utmpcopy.c 
 *
 *	purpose:	copy some number of records from a utmp file
 *	args:		source #toskip #tocopy
 *	action:		open the file and seek to start record
 *			the copy until count exhausted or eof
 *	compiling:	to compile this, use
 *			gcc utmpcopy.c -o utmpcopy
 *
 *	usage:		utmpcopy /var/log/wtmp 10 100 > wtmp.sample
 */

#include	<stdio.h>
#include	<sys/types.h>
#include	<utmp.h>
#include	<fcntl.h>

int main(int ac,char **av)
{
	int	fd;
	int	n;
	struct utmp buf;
	int	l = sizeof(buf);
	int	nread;

	if ( ac != 4 ){
		fprintf(stderr,"usage: utmpcopy source #skip #tocopy\n");
		exit(1);
	}
	fd = open(av[1],O_RDONLY);
	if ( fd == -1 ){
		perror(av[1]); exit(1);
	}
	if ( lseek(fd, atol(av[2])*l, SEEK_SET) == -1 ){
		perror("lseek"); exit(2);
	}
	n = atoi(av[3]);
	while( n-- > 0  && read(fd,&buf,l) == l && write(1,&buf,l) == l )
	       ;
	close(fd);
	return 0;
}
