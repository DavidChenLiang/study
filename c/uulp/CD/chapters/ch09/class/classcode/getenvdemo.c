

main()
{
	char	*cp, *getenv();

	printf("your terminal type is %s\n", getenv("TERM"));
	printf("your dog is named %s\n", getenv("DOG") );
}
