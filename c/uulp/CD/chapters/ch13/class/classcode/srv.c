
/****************************************************************************
 * srv.c
 * License server server program
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <sys/errno.h>

#define SERVER_PORTNUM	2020		/* Our server's port number */
#define MSGLEN		128		/* Size of our datagrams */
#define TICKET_AVAIL	-1		/* Slot is available for use */
#define EXPIRE_INTERVAL 60		/* Expire every 60 seconds */
#define MAXUSERS	3		/* Only 3 users for us */
#define	REPORT_PREFIX	"\t\t\tSRV:"
#define	SYSERROR(x)	{ perror(x); exit(-1); }

/****************************************************************************
 * Important variables
 */
static int ticket_array[MAXUSERS];	/* Our ticket array */
static int sd = -1;			/* Our socket */
static int num_tickets_out = 0;		/* Number of tickets outstanding */
extern int errno;

/****************************************************************************
 * shut_down
 * Shut down cleanly when we get a signal.
 * Results: NEVER RETURNS
 */
void shut_down()
{
	/* Close socket and exit */
	(void) shutdown(sd, 2);
	(void) close(sd);
	exit(0);
} /* shut_down */

/****************************************************************************
 * ticket_expire
 * go through all tickets and get rid of any dead ones
 * Results: none
 */
void ticket_expire()
{
	int x;

	/* Go through the array and look for tickets that belong to 
	 * processes that are dead.
	 */
	for(x = 0; x < MAXUSERS; x++) {
		if((ticket_array[x] != TICKET_AVAIL) &&
		   (kill(ticket_array[x], 0) == -1) && (errno == ESRCH)) {
			/* Process is gone - free up slot */
			fprintf(stderr, 
				"%s Process %d gone - freeing ticket\n",
					REPORT_PREFIX, ticket_array[x]);
			ticket_array[x] = TICKET_AVAIL;
			num_tickets_out--;
		}
	}

	/* Now reset the alarm clock */
	(void) alarm(EXPIRE_INTERVAL);
	return;
} /* ticket_expire */

/****************************************************************************
 * do_hello
 * Give out a ticket if any are available
 * IN  msg_p			message received from client
 * Results: ptr to response
 * 				NOTE: return is in static buffer overwritten
 * 				by each call.
 */
static char *do_hello(msg_p)
char *msg_p;
{
	int x;
	static char replybuf[MSGLEN];

	/* Got a ticket request - see if we can give out a ticket. */
	if(num_tickets_out >= MAXUSERS) {
		/* No tickets available */
		return("FAIL no tickets available");
	} else {
		/* Give out a ticket */
		for(x = 0; x < MAXUSERS; x++) 
			if(ticket_array[x] == TICKET_AVAIL) 
				break;

		/* Just a sanity check - should never happen */
		if(x == MAXUSERS) {
			fprintf(stderr, "%s database corrupt\n",
					REPORT_PREFIX);
			return("FAIL database corrupt");
		} else {
			/* Got it OK! We'll make a ticket for this process
			 * and keep track of the PID (their "name") and
			 * the slot it's in (the "dongle number").
			 *
			 * Thus, our ticket string looks like:
			 * 	pid.slot
			 */
			ticket_array[x] = atoi(msg_p + 5); /* get pid in msg */
			sprintf(replybuf, "TICK %d.%d", ticket_array[x], x);
			num_tickets_out++;
		}
	}
	
	/* Return our response */
	return(replybuf);

} /* do_hello */

/****************************************************************************
 * do_goodbye
 * Take back ticket client is returning
 * IN  msg_p			message received from client
 * Results: ptr to response
 * 				NOTE: return is in static buffer overwritten
 * 				by each call.
 */
static char *do_goodbye(msg_p)
char *msg_p;
{
	int pid, slot;		/* components of ticket	*/

	/* The user's giving us back a ticket.  First we need to get
 	 * the ticket out of the message, which looks like:
	 *
	 * 	GBYE pid.slot
	 */
	if((sscanf((msg_p + 5), "%d.%d", &pid, &slot) != 2) ||
	   (ticket_array[slot] != pid)) {
		fprintf(stderr, "%s Bogus ticket \"%s\"\n", msg_p + 5,
				REPORT_PREFIX);
		return("FAIL invalid ticket");
	}

	/* The ticket is valid.  Release it. */
	ticket_array[slot] = TICKET_AVAIL;
	num_tickets_out--;

	/* Return response */
	return("TATA See ya!");

} /* do_goodbye */

/****************************************************************************
 * do_validate
 * Validate client's ticket
 * IN  msg_p			message received from client
 * Results: ptr to response
 * 				NOTE: return is in static buffer overwritten
 * 				by each call.
 */
static char *do_validate(msg_p)
char *msg_p;
{
	int pid, slot;          /* components of ticket */

	/* The user's giving us a ticket to validate.  First we need to get
 	 * the ticket out of the message, which looks like:
	 *
	 * 	VALD pid.slot
	 */
	if((sscanf((msg_p + 5), "%d.%d", &pid, &slot) != 2) ||
	   (ticket_array[slot] != pid)) {
		fprintf(stderr, "%s Bogus ticket \"%s\"\n", 
				REPORT_PREFIX, msg_p + 5);
		return("FAIL invalid ticket");
	}
	/* If we got here the ticket's good */
	return("GOOD Valid ticket");
} /* do_validate */

/****************************************************************************
 * main
 * main processing loop for server program
 * Results: none
 */
main()
{
	int pid;
	char buf[MSGLEN];
	int secs_left = EXPIRE_INTERVAL;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int addrlen;
	char *resp_p;
	int x;
	char *inet_ntoa();

        struct  sockaddr_in   saddr;   /* build our address here */
	struct	hostent		*hp;   /* this is part of our    */
	char	hostname[256];         /* address 	         */
	int	slen,sock_id,sock_fd;  /* line id, file desc     */
	FILE	*sock_fp;              /* use socket as stream   */
        char    *ctime();              /* convert secs to string */
        long    time(), thetime;       /* time and the val       */ 

        gethostname( hostname );                /* where am I ?         */
        hp = gethostbyname( hostname );         /* get info about host  */

        bzero( &saddr, sizeof(saddr) );         /* zero struct          */
				       /* fill in hostaddr     */
        bcopy( hp->h_addr, &saddr.sin_addr, hp->h_length);
        saddr.sin_family = AF_INET ;            /* fill in socket type  */
        saddr.sin_port = htons(SERVER_PORTNUM); /* fill in socket port  */

       /*
        *      step 2: ask kernel for a socket, then bind address
        */

        sd = socket( AF_INET, SOCK_DGRAM, 0 );    /* get a socket */
        if ( sd == -1 ) 
	        SYSERROR("SERVER: socket");

        if ( bind(sd, &saddr, sizeof(saddr)) != 0 )/* bind it to   */
	        SYSERROR("SERVER: bind");

        /* Set up signal handler to clean up on exit */
	(void) signal(SIGINT, shut_down);
	(void) signal(SIGTERM, shut_down);

#ifdef EXPIRE_TICKETS
	/* Set up the alarm clock */
	(void) signal(SIGALRM, ticket_expire);
	alarm(EXPIRE_INTERVAL);
#endif /* EXPIRE_TICKETS */

	/* Initialize ticket database */
	for(x = 0; x < MAXUSERS; x++)
		ticket_array[x] = TICKET_AVAIL;

	/* Set up a loop, listening to client requests forever */
	while(1) {
		/* Get a request */
		addrlen = sizeof(client_addr);
		if(recvfrom(sd, buf, MSGLEN, 0, &client_addr, &addrlen) == -1) {
			/* If we get an error we'll acknowledge it, but we
			 * must continue so that we can help other clients.
			 * 
			 * We ignore EINTR; that's just the alarm handler
			 */
			if(errno != EINTR)
				perror("SERVER: recvfrom");

			continue;
		}
		fprintf(stderr, "%s Got \"%s\" from %s,%d\n", 
			REPORT_PREFIX, 
			buf,
			inet_ntoa(client_addr.sin_addr),
			client_addr.sin_port);

#ifdef EXPIRE_TICKETS
		/* Turn off the alarm clock so we're not interrupted in
		 * the middle of things.
		 */
		secs_left = alarm(0);
#endif /* EXPIRE_TICKETS */

		/* Is this a request we know how to deal with?  If so,
		 * do so.  If not, send a failure message back.
		 * We recognize the following:
		 * 	HELO client-id-string
		 *	GBYE ticket-id-string
		 * 	VALD ticket-id-string
		 */
		if(strncmp(buf, "HELO", 4) == 0) 
			resp_p = do_hello(buf);
		else if(strncmp(buf, "GBYE", 4) == 0)
			resp_p = do_goodbye(buf);
		else if(strncmp(buf, "VALD", 4) == 0)
			resp_p = do_validate(buf);
		else
			resp_p = "FAIL Invalid Request";

		/* Now send the response */
		fprintf(stderr, "%s sending response \"%s\"\n",
				REPORT_PREFIX, resp_p);

		if(sendto(sd, resp_p, MSGLEN, 0, &client_addr, addrlen) == -1) {
			/* If we get an error we'll acknowledge it, but we
			 * must continue so that we can help other clients.
			 */
			perror("SERVER: sendto");
			continue;
		}

#ifdef EXPIRE_TICKETS
		/* Turn the alarm clock back on since we're idle again */
		if(secs_left == 0)
			secs_left = EXPIRE_INTERVAL;	/* Reset timer */
		(void) alarm(secs_left);
#endif /* EXPIRE_TICKETS */

		/* Just go back and get the next msg! */
	}
	/* NOTREACHED */
} /* main */
