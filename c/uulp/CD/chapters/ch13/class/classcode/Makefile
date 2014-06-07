
all: basic expire validate

# The basic client and server - nothing fancy
basic: srv1 clnt1

# The basic client, plus the ticket expire stuff in the server
expire: srv2 clnt2

# The server with the ticket expire stuff + client ticket validation
validate: srv3 clnt3

clnt1: clnt.c
	cc -o clnt1 clnt.c

clnt2: clnt.c
	cc -o clnt2 clnt.c

clnt3: clnt.c
	cc -DVALIDATE_TICKETS -o clnt3 clnt.c

srv1: srv.c
	cc -o srv1 srv.c

srv2: srv.c
	cc -DEXPIRE_TICKETS -o srv2 srv.c

srv3: srv.c
	cc -DEXPIRE_TICKETS -o srv3 srv.c

clean:
	rm -f srv1 srv2 srv3 clnt1 clnt2 clnt3

