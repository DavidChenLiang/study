
#include	<stdio.h>

main()
{
	char	mydir[BUFSIZ];

	mygetcwd( mydir );
	printf(" We are in %s\n", mydir);
}

mygetcwd( buf )
char *buf;
/*
 *	create a new process and a pipe to read from the child
 *	before exec'ing pwd
 *
 *	logic of this program:	(need to use fork, exec, pipe, fdopen )
 *
 *	
 */
{
	int	apipe[2];		/* need this to talk to child	*/

	if ( pipe(apipe) == -1 )		/* get a nice pipe	*/
	{
		perror("pipe failed");
		exit(1);
	}

	switch ( fork() )			/* and a process	*/
	{
		case -1:			/* bad news		*/
			perror("fork failed");
			exit(1);
		case  0:
			go_do_pwd(apipe);
			break;	
		default:
			get_info_into(buf, apipe);
			break;	
	}
}

go_do_pwd( apipe )
int apipe[2];
/*
 *	set up pipe for writing in place of stdout
 *	then exec pwd
 */
{
	close(1);			/* release current stdou	*/
	dup(apipe[1]);			/* dupe writing end of pipe	*/
	close(apipe[0]);		/* close readng end		*/
	close(apipe[1]);		/* this is duped already	*/

	/* connections all set up  now for the work			*/

	execlp("pwd", "pwd", NULL );
}

get_info_into(b, pipearray)
char *b;
int pipearray[];
/*
 *	read a line from the reading end of the pipe
 *	and put it in b
 *
 *	could use read, but let's fdopen and fscanf()
 */
{
	FILE	*fp, *fdopen();		/* define fd, declare fdopen	*/

	fp = fdopen(pipearray[0],"r");	/* convert to a stream		*/
	if ( fp == NULL )
		exit(12);		/* obscure error codes		*/
					/* thinks: must document this	*/

	fscanf(fp, "%s", b);		/* get a string			*/

	fclose(fp);			/* close connection		*/
}
