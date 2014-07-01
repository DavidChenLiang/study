#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <stdlib.h>

#define oops(msg)   {perror(msg);exit(1);}

int
main(int argc, char *av[]){
    struct   sockaddr_in    servadd;
    struct   hostent        *hp;
    int      sock_id,sock_fd;
    char     message[BUFSIZ];
    int      messlen;
    
    /*step 1*/
    sock_id = socket(AF_INET, SOCK_STREAM,0);
    if (sock_id == -1) oops("socket");
    
    /*step 2*/
    bzero(&servadd,sizeof(servadd));
    
    hp = gethostbyname(av[1]);
    if (hp == NULL) oops(av[1]);
    bcopy(hp->h_addr, (struct sockaddr *)&servadd.sin_addr,hp->h_length);
    servadd.sin_port = htons(atoi(av[2]));
    
    servadd.sin_family = AF_INET;
    if (connect(sock_id,(struct sockaddr *)&servadd,sizeof(servadd)) != 0) oops("Connect");
    /*step 3*/
    messlen = read(sock_id, message, BUFSIZ);
    if (messlen == -1) oops("read");
    if (write(stdout,message,messlen) != messlen) oops("Write");
    close(sock_id);
    exit(EXIT_SUCCESS);
}


