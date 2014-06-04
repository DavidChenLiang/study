/** qvsend.c
 *
 *  send a message to the qvis server at a particular key
 *
 *  usage: qvsend key qnum "message here"
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAXMSG 100

struct msg_t {
		long type;
		char data[MAXMSG];
	};

main(int ac, char *av[])
{
	struct msg_t message;
	int	qd;

	if ( ac != 4 ){
		fprintf(stderr,"usage: qvsend key qnum msg\n");
		exit(1);
	}
	/* connect to q */
	qd = msgget((key_t) atoi(av[1]),0);

	message.type = atol(av[2]);
	av[3][MAXMSG-1] = '\0';
	strcpy(message.data,av[3]);

	if ( msgsnd(qd,&message,sizeof(message),0) == -1 )
		perror("msgsend");
}
