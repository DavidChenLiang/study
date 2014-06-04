#include	<stdio.h>
#include	<signal.h>

int	haha();

main()
{
	int	i = 0;
	

	signal( SIGINT, haha );
	while(1)
	{
		printf("You can't kill me! %d \n", i++);
		sleep(1);
	}
}

haha()
{
	printf("hahah, you can't kill me!\n");
}
