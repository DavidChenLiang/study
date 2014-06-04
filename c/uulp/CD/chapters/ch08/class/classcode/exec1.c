

main()
{
	char	*arglist[4];

	arglist[0] = "ls";
	arglist[1] = "-l";
	arglist[2] = "/bin";
	arglist[3] = 0 ;
	execvp( "ls" , arglist );
	printf("ls is done. bye\n");
}
