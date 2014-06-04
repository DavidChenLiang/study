#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<strings.h>

/*
 * WebServ1.c - a minimal web server
 *
 *    usage: ws portnumber
 * features: supports the GET command only
 *           runs in the current directory
 *           forks a new child to handle each request
 *           has MAJOR security holes, for demo purposes only
 *           has many other weaknesses, but is a good start
 */

main(int ac, char *av[])
{
	int 	sock, fd;
	FILE	*fpin;
	char	request[BUFSIZ];

	if ( ac == 1 ){
		fprintf(stderr,"usage: ws portnum\n");
		exit(1);
	}
	sock = make_server_socket( atoi(av[1]) );
	if ( sock == -1 ) exit(2);

	/* main loop here */

	while(1){
		/* take a call and buffer it */
		fd = accept( sock, NULL, NULL );
		fpin = fdopen(fd, "r" );

		/* read request */
		fgets(request,BUFSIZ,fpin);
		printf("got a call: request = %s", request);
		read_til_crnl(fpin);

		/* do what client asks */
		process_rq(request, fd);

		fclose(fpin);
	}
}

/* ------------------------------------------------------ *
   read_til_crnl(FILE *)
   skip over all request info until a CRNL is seen
   ------------------------------------------------------ */

read_til_crnl(FILE *fp)
{
	char	buf[BUFSIZ];
	while( fgets(buf,BUFSIZ,fp) != NULL && strcmp(buf,"\r\n") != 0 )
		;
}

/* ------------------------------------------------------ *
   process_rq( char *rq, int fd )
   do what the request asks for and write reply to fd 
   handles request in a new process
   rq is HTTP command:  GET /foo/bar.html HTTP/1.0
   ------------------------------------------------------ */

process_rq( char *rq, int fd )
{
	char	cmd[BUFSIZ], arg[BUFSIZ];
	char	*item;

	/* create a new process and return if not the child */
	if ( fork() != 0 )
		return;

	if ( sscanf(rq, "%s%s", cmd, arg) != 2 )
		return;
	item = arg+1;			/* skip leading / */
	if ( strcmp(cmd,"GET") != 0 )
		cannot_do(fd);
	else if ( not_exist( item ) )
		do_404(item, fd );
	else if ( isadir( item ) )
		do_ls( item, fd );
	else if ( ends_in_cgi( item ) )
		do_exec( item, fd );
	else
		do_cat( item, fd );
}

/* ------------------------------------------------------ *
   the reply header thing: all functions need one
   if content_type is NULL then don't send content type
   ------------------------------------------------------ */

header( FILE *fp, char *content_type )
{
	fprintf(fp, "HTTP/1.0 200 OK\r\n");
	if ( content_type )
		fprintf(fp, "Content-type: %s\r\n", content_type );
}

/* ------------------------------------------------------ *
   simple functions first:
        cannot_do(fd)       unimplemented HTTP command
    and do_404(item,fd)     no such object
   ------------------------------------------------------ */

cannot_do(int fd)
{
	FILE	*fp = fdopen(fd,"w");

	fprintf(fp, "HTTP/1.0 501 Not Implemented\r\n");
	fprintf(fp, "Content-type: text/plain\r\n");
	fprintf(fp, "\r\n");

	fprintf(fp, "That command is not yet implemented\r\n");
	fclose(fp);
}

do_404(char *item, int fd)
{
	FILE	*fp = fdopen(fd,"w");

	fprintf(fp, "HTTP/1.0 504 Not Found\r\n");
	fprintf(fp, "Content-type: text/plain\r\n");
	fprintf(fp, "\r\n");

	fprintf(fp, "The item you requested: %s\r\nis not found\r\n", 
			item);
	fclose(fp);
}

/* ------------------------------------------------------ *
   the directory listing section
   isadir() uses stat, not_exist() uses stat
   do_ls runs ls. It should not
   ------------------------------------------------------ */

isadir(char *f)
{
	struct stat info;
	return ( stat(f, &info) != -1 && S_ISDIR(info.st_mode) );
}

not_exist(char *f)
{
	struct stat info;
	return( stat(f,&info) == -1 );
}

do_ls(char *dir, int fd)
{
	FILE	*fp ;
	int	pid;

	fp = fdopen(fd,"w");
	header(fp, "text/plain");
	fprintf(fp,"\r\n");
	fflush(fp);

	dup2(fd,1);
	dup2(fd,2);
	close(fd);
	execlp("ls","ls","-l",dir,NULL);
	perror(dir);
	exit(1);
}

/* ------------------------------------------------------ *
   the cgi stuff.  function to check extension and
   one to run the program.
   ------------------------------------------------------ */

char *
file_type(char *f)
/* returns 'extension' of file */
{
	char	*cp;
	if ( cp = strrchr(f, '.' ) )
		return cp+1;
	return "";
}

ends_in_cgi(char *f)
{
	return ( strcmp( file_type(f), "cgi" ) == 0 );
}

/*
 * executes a program with stdout sent to client via socket
 */
do_exec( char *prog, int fd )
{

	/* exercise for reader */
	
}
/* ------------------------------------------------------ *
   do_cat(filename,fd)
   sends back contents after a header
   e.g. .html gets  Content-type: text/html
        .gif  gets  Content-type: image/gif
   ------------------------------------------------------ */

do_cat(char *f, int fd)
{
	FILE	*fpsock, *fpfile;
	char	*ext;
	int	c;

	fpsock = fdopen( fd, "w" );
	fpfile = fopen( f, "r" );

	fprintf(fpsock,"HTTP/1.0 200 OK\r\n");
	ext = file_type( f );
	if ( strcmp( ext, "html" ) == 0 )
		fprintf(fpsock,"Content-type: text/html\r\n");
	else if ( strcmp( ext, "txt" ) == 0 )
		fprintf(fpsock,"Content-type: text/plain\r\n");
	else if ( strcmp( ext, "jpeg" ) == 0 || strcmp(ext,"jpg") == 0 )
		fprintf(fpsock,"Content-type: image/jpeg\r\n");
	else if ( strcmp( ext, "gif" ) == 0 )
		fprintf(fpsock,"Content-type: image/gif\r\n");
	else if ( strcmp( ext, "mp3" ) == 0 )
		fprintf(fpsock,"Content-type: x-audio/mp3\r\n");
	else 
		fprintf(fpsock,"Content-type: text/plain\r\n");
	fprintf(fpsock,"\r\n");

	while( ( c = getc(fpfile) ) != EOF )
		putc(c, fpsock);
	fclose(fpfile);
	fclose(fpsock);
}
