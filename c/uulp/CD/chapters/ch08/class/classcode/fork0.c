#include	<stdio.h>

main()
{
	printf("hello, I am a program about to fork..\n");
	fflush(stdout);

	fork();

	printf("hello, here I am after thje fork.  do I look different?\n");
	fflush(stdout);

	printf("that was fun. Let's do it againn...\n");
	fork();

	printf("wow.  does that do anything interesting?\n");
	
}
