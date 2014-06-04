#include	<stdio.h>
#include	<string.h>

/*
 * a pop shell,
 *
 * this program allows one to connect to and talk to a pop server
 * It uses the servconn.c library to connect to an communicate
 * with the pop server.
 *
 */

#define	STRMAX	512

/* declarations of servconn functions */

int SCconnect();
int SCtell_server();
int SCgetstr();

/* declarations of functions here */

int poplogin();
int get_next_cmd();
int show_reply();
int in_list();


int
main()
{
	char	buf[STRMAX];

	if ( poplogin() == -1 )
		exit(1);
	while( get_next_cmd(buf) == 0 )
	{
		if ( SCtell_server(buf) == -1 )
			break;
		if ( show_reply(buf) == -1 )
			break;
	}
	return 0;
}

int
poplogin()
/* 
 * purpose: ask user for hostname, logname, and password, then connect
 */
{
	char	host[STRMAX], user[STRMAX], pass[STRMAX];
	char	buf[STRMAX];
	int	system();


	printf("hostname? ");
	fgets(host,STRMAX,stdin); host[strlen(host)-1] = '\0';

	printf("username? ");
	fgets(user,STRMAX,stdin); user[strlen(user)-1] = '\0';

	system("stty -echo");
	printf("password? ");
	fgets(pass,STRMAX,stdin); pass[strlen(pass)-1] = '\0';
	system("stty echo");
	putchar('\n');
	
	/* now make a connection and login */

	if ( SCconnect(host) == -1 )
		return -1;
	if ( SCgetstr(buf,STRMAX) == -1 )	/* server says hello */
		return -1;
	printf("[connected to mailbox for %s@%s: \n %s]\n", user, host, buf+4);

	/* send user command */
	sprintf(buf, "USER %s", user);
	if ( SCtell_server( buf ) == -1 )
		return -1;
	if ( SCgetstr(buf,STRMAX) == -1 )
		return -1;
	if ( strncmp(buf,"+OK",3) != 0 )
		return -1;

	/* send pass command */
	sprintf(buf, "PASS %s", pass);
	if ( SCtell_server( buf ) == -1 )
		return -1;
	if ( SCgetstr(buf,STRMAX) == -1 )
		return -1;
	if ( strncmp(buf,"+OK",3) != 0 )
		return -1;

	return 0;
}

int
get_next_cmd(char *str)
/*
 * purpose: read next lnie of input from user
 *     arg: a buffer 
 * returns: -1 on error, 0 if ok
 *   notes: skips blank lines, 
 */
{
	while( printf("popsh$ "), fgets(str,STRMAX,stdin)  != NULL ){
		str[strlen(str)-1] = '\0';
		if ( strlen(str) > 0 )
			return 0;
	}
	return -1;
}

char	*one_line_cmds[] = { 	"USER", "PASS", "STAT", "QUIT", "DELE",
				"RSET", "NOOP", NULL };
char	*multi_ln_cmds[] = { 	"RETR", "LIST", "TOP", NULL };


int
show_reply(char *str)
/*
 * purpose: display respnse from server
 *     arg: the str that was sent
 * returns: -1 on error, 0 if ok
 *   notes: some commands expect one-line reply, some
 *	    expect multi-line.  Need to loop for those.
 */
{
	char	*cp;
	char	buf[STRMAX];
	int	rv = 0;

	if ( (cp = strchr(str,' ')) != NULL )/* chop cmd at first space */
		*cp = '\0';

	if ( in_list( str, multi_ln_cmds ) )
		do {
			rv = SCgetstr(buf,STRMAX);
			if ( rv == -1 )
				break;
			printf("%s\n", buf);
		} 
		while( strcmp(buf,".") != 0 );
	else {
		rv = SCgetstr(buf,STRMAX);
		printf("%s\n", buf);
	}

	return rv;
}


int
in_list( char *lookfor, char *list[] )
/*
 * does case-independent seararch for string
 */
{
	int	i;
	for( i = 0 ; list[i] != NULL ; i++ )
		if ( strcasecmp(lookfor,list[i]) == 0 )
			return 1;
	return 0;
}
