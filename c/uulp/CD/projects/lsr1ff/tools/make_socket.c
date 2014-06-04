#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/un.h>

main()
{
	int	sd;
	int	cd;
	struct  sockaddr_un add;
	int	rv;
	char	buf[512];
	int	n;

	sd = socket(AF_UNIX,SOCK_STREAM,0);
	if ( sd == -1 ){
		perror("socket");
		exit(1);
	}
	
	add.sun_family = AF_UNIX;
	strcpy(add.sun_path, "mysocket");
	rv = bind(sd, (struct sockaddr *)&add, sizeof(add));
	if ( rv == -1 ){
		perror("bind");
		exit(1);
	}
	printf("ok!\n");
	if ( listen(sd, 3) == -1 ){
		perror("listen");
		exit(1);
	}
	exit(0);
}
