/****************************************************************************
 * clnt.c
 * License server client
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORTNUM	2020		/* Our server's port number */
#define MSGLEN		128		/* Size of our datagrams */
#define oops(p) { perror(p); exit(1) ; }

/****************************************************************************
 * Important variables used throughout
 */
static int pid = -1;			/* Our PID */
static int sd = -1;			/* Our communications socket */
static struct sockaddr_in server_addr;	/* Server address */	
static char ticket_buf[128];		/* Buffer to hold our ticket */
static have_ticket = 0;			/* Set when we have a ticket */

/****************************************************************************
 * do_transaction
 * Send a request to the server and get a response back
 * IN  sd		socket descriptor
 * IN  msg_p		message to send
 * IN  addr_p		server's address
 * Results: pointer to message string, or NULL for error
 *			NOTE: pointer returned is to static storage 
 *			overwritten by each successive call.
 */
static char *do_transaction(sd, msg_p, addr_p)
int sd;
char *msg_p;
struct sockaddr_in *addr_p;
{
	static char buf[MSGLEN];

	struct sockaddr_in retaddr;
	int addrlen;
	int ret;
	
	/* First send the message */
	strncpy(buf, msg_p, MSGLEN);
	if((ret = sendto(sd, buf, MSGLEN, 0, addr_p, 
	    sizeof(struct sockaddr_in))) == -1) {
		sprintf(buf, "CLIENT [%d]: sendto", pid);
		perror(buf);
		return((char *) 0);
	}

	/* Get the response back */
	if((ret = recvfrom(sd, buf, MSGLEN, 0, &retaddr, &addrlen)) == -1) {
		sprintf(buf, "CLIENT [%d]: recvfrom", pid);
		perror(buf);
		return((char *) 0);
	}

	/* Now return the message itself */
	return(buf);
} /* do_transaction */

/****************************************************************************
 * get_ticket
 * get a ticket from the license server
 * Results: 0 for success, 1 for failure
 */
static int get_ticket()
{
	char *resp_p;
	char buf[MSGLEN];

	/* If we already have a ticket, don't ask for another */
	if(have_ticket)
		return(0);

	/* Now set up a request to send to the server.  We use our
	 * PID to identify ourselves to the server.
	 */
	sprintf(buf, "HELO %d", pid);

	/* Perform the transaction itself */
	if((resp_p = do_transaction(sd, buf, &server_addr)) == (char *) 0)
		return(-1);

	/* Now parse the response and see if we got a ticket.  If we did,
	 * the message will be:
	 * 	TICK ticket-string
	 * If not, it will be:
	 * 	FAIL failure-msg
	 */
	if(strncmp(resp_p, "TICK", 4) != 0) {
		if(strncmp(resp_p, "FAIL") != 0) {
			fprintf(stderr, "CLIENT [%d]: unknown msg \"%s\"\n", 
				pid, resp_p);
			return(-1);
		} else {
			fprintf(stderr, "CLIENT [%d]: couldn\'t get ticket.\n",
				pid);
			return(-1);
		}
	} else 
		fprintf(stderr, "CLIENT [%d]: got ticket!\n", pid);

	/* Save the ticket string */
	strcpy(ticket_buf, resp_p + 5);	/* ticket-string after "TICK " */
	have_ticket = 1;		/* We have a ticket */
	return(0);
} /* get_ticket */
  
/****************************************************************************
 * release_ticket
 * Give a ticket back to the server
 * Results: 0 for success, -1 for failure
 */
static int release_ticket()
{
	char buf[MSGLEN];
	char *resp_p;

	/* If we don't have one, there's none to give back */
	if(!have_ticket)
		return(0);

	/* Now we'll give it back - format the message */
	sprintf(buf, "GBYE %s", ticket_buf);

	/* Perform the transaction itself */
	if((resp_p = do_transaction(sd, buf, &server_addr)) == (char *) 0)
		return(-1);

	/* Now see what the server sent us.  If everything went OK, we'll
	 * get a message like:
	 * 	TATA info-string
	 * If it failed, we'll get a message like:
	 * 	FAIL error-string
	 * Otherwise, something we don't understand went wrong.
	 */
	if(strncmp(resp_p, "TATA", 4) == 0) {
		fprintf(stderr, "CLIENT [%d]: released ticket OK\n", pid);
		return(0);
	} else if(strncmp(resp_p, "FAIL", 4) == 0)
		fprintf(stderr, "CLIENT [%d]: release failed \"%s\"\n", 
			pid, resp_p + 5);
	else
		fprintf(stderr, "CLIENT [%d]: unknown response \"%s\"\n", 
			pid, resp_p);

	/* Something went wrong */
	return(-1);
} /* release_ticket */

/****************************************************************************
 * validate_ticket
 * Make sure the ticket we have is still good
 * Results: 0 for success, -1 for failure
 */
static int validate_ticket()
{
	char buf[MSGLEN];
	char *resp_p;

	/* If we don't have one, there's none to validate */
	if(!have_ticket)
		return(-1);

	/* If we're not validating, we skip the test, and just always say 
	 * it's OK
	 */
#ifdef VALIDATE_TICKETS
	sprintf(buf, "VALD %s", ticket_buf);

	/* Send the message - don't exit if this fails, since we must
	 * free the ticket!
	 */

	/* Perform the transaction itself - don't exit if we can't reach
 	 * the server, though, as we still have to free the ticket.
	 */
	if((resp_p = do_transaction(sd, buf, &server_addr)) == (char *) 0) {
		have_ticket = 0;
		return(-1);
	}

	/* Now make sure we got a valid response.  We should either get
 	 * back a validation:
	 * 	GOOD response-string
	 * or a failure:
	 * 	FAIL error-string
	 */
	if(strncmp(resp_p, "FAIL", 4) == 0) {
		/* We got a failure msg - the ticket's no good, so exit. */
		fprintf(stderr, "CLIENT [%d]: validation failed - \"%s\"\n", 
			pid, buf + 5);
		have_ticket = 0;
		return(-1);
	} else if(strncmp(resp_p, "GOOD", 4) != 0) {
		/* We don't know what we got - get out of here */
		fprintf(stderr, "CLIENT [%d]: unknown msg - \"%s\"\n",
			pid, buf + 5);
		have_ticket = 0;
		return(-1);
	}
#endif /* VALIDATE_TICKETS */

	/* we validated OK */
	return(0);
} /* validate_ticket */

/****************************************************************************
 * main
 * main processing loop for client program
 * Results: none
 */
main()
{
	char buf[MSGLEN];
	struct hostent      *hp;            /* used to get number */
        char   message[BUFSIZ];             /* to receive message */
        int    messlen;                     /* for message length */
	char   hostname[256];

       /*
        *      build the network address of where we want to call
        */

        gethostname( hostname );
        hp = gethostbyname( hostname );
        if ( hp == NULL ) oops("no such computer");

        bzero( &server_addr, sizeof( server_addr ) );   /* zero the address     */
        server_addr.sin_family = AF_INET ;              /* fill in socket type  */
                                                       /* and machine address  */
        bcopy( hp->h_addr, &server_addr.sin_addr, hp->h_length);
        server_addr.sin_port = htons(SERVER_PORTNUM);   /* host to num short    */


	/* Set our PID so we can use it in msgs, etc. later */
	pid = getpid();

	/* Set up a datagram socket. */
	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("CLIENT: socket");
		exit(-1);
	}

	/* Try to get a ticket - get_ticket() prints a message if this
	 * part fails.
 	 */
	if(get_ticket()) 
		exit(-1);

	/* If we got here OK, we got a ticket.  Let's just go to sleep for
	 * a few seconds, and then we'll release it.
	 */
	fprintf(stderr, "CLIENT [%d]: sleeping...\n", pid);
	sleep(10);

#ifdef	VALIDATE_TICKETS
	/* Now let's try and validate the ticket */
	if(validate_ticket())				/* Version 3 only */
	{
		fprintf(stderr,
			"CLIENT [%d]: have a bogus ticket!!\n", pid);
		exit(-1);
	}

	/* If we got here, we validated OK. */
	fprintf(stderr, 
		"CLIENT [%d]: validated ticket - sleeping some more ...\n",
		pid);
	sleep(5);
#endif /* VALIDATE_TICKETS */

	/* Release the ticket */
	(void) release_ticket();

	/* Now we're done.  Let's just clean up and get out of here */
	fprintf(stderr, "CLIENT [%d]: released ticket.  exiting...\n", pid);
	(void) close(sd);
	exit(0);
} /* main */

