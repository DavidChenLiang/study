/** qvis.c
 *
 * purpose: visual display of messages arriving on N msg queues
 * display: prints messages in different columns based on msgtype
 *   notes: would look nice with a curses or X interface to show
 *          each Q in a separate scrolling window.
 *
 *   usage: qvis id [wid]
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define MAXDATA	100
#define COLWID  20
struct message {
	long msg_type;
	char data[MAXDATA];
};

#define	oops(m,x) { perror(m); exit(x); }

int	         qd;

int
main(int ac, char *av[])
{
	struct message   msg;
	long		 msgtype;
	void		 wrapup(int);
	int		 numqueues;
	int		 colwid = COLWID;

	signal(SIGINT,wrapup);
	
	if ( ac < 2 ){
		fprintf(stderr,"usage: qshow qid [colwid]\n");
		exit(1);
	}
	/* make the msg queue */
	qd = msgget((key_t)atoi(av[1]), 0666|IPC_CREAT);
	if ( qd == -1 )
		oops("msgget", 1);
	if ( ac > 2 )
		colwid = atoi(av[2]);

	while(1){
		if ( msgrcv(qd,&msg,sizeof(msg),0,0) == -1 )
			oops("msgrcv",2);
		msgtype = msg.msg_type;
		printf("%*s%s\n", msgtype*colwid,"",msg.data);
	}
}

void
wrapup(int s)
{
	msgctl(qd,IPC_RMID,NULL);
	exit(0);
}
