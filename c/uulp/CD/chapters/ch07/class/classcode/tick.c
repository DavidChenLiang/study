#include <stdio.h>
#include <signal.h>

main()
{
	void hi();

	signal( SIGALRM, hi );
	set_ticker(4000);
	while(1)
	{
		write(1, " *\b", 3);
		sleep(1);
	}
}

void hi()
{
	printf("Hi!");
	fflush(stdout);
}
