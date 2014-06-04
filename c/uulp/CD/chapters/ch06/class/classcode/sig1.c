
#include	<stdio.h>
#include	<signal.h>

main()
{
	void	f();

	signal( SIGINT, f );
	while(1)
	{
		printf("hello\n");
		sleep(1);
	}
}

void f()
{
	printf("OUCH!\n");
}
