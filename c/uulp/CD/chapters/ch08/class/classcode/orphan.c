

main()
{
	printf("hi, about to fork\n");

	if ( fork() == 0 ){
		printf("My parent is %d\n", getppid());
		sleep(5);
		printf("My parent is %d\n", getppid());
		exit(2);
	}
	/* parent here */

	printf("had a child...\n");
	sleep(2);
	exit(5);
}
