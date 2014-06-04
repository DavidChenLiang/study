

main()
{
	int	pid ;

	pid = fork();

	if ( pid == 0 )
	{
		exit(2);
	}

	sleep(20);
	printf("I gotta go now.  My meter is about to run out!\n");
	exit(3);
}
