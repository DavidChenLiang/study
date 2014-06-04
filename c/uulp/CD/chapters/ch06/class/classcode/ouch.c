#include <signal.h>

main()
{
	int	i = 0;
	void ouch(int);

	signal(SIGINT, ouch);
	signal(SIGQUIT, ouch);
	while(1){
		printf("hello\n");
		sleep(1);
		i++;
		if ( i == 10 )
			signal(SIGINT, SIG_DFL);
	}
}

void ouch(int n)
{
	static int times = 0;

	times++;
	printf("   \aOuch! for time number %d my arg was %d\n",times, n);
}
