#include	<stdio.h>
#include	<signal.h>

int	otherpid;

main()
{
	int	ouch();
	int	newpd;

	signal(SIGINT, ouch);

	switch( newpd = fork() )
	{
		case -1:	exit(1);

		case 0:
				while(1)
				{
				sleep(3);
				otherpid = getppid();
				kill( getppid(), SIGINT );
				}
		default:
				otherpid = newpd ;
				while(1)
				{
				printf("parent here.  thngs look ok\n");
				sleep(1);
				}
	}
}
ouch()
{
	printf("I just got a sigint.  Maybe from %d\n", otherpid);
	kill( otherpid, SIGINT );
}
				
