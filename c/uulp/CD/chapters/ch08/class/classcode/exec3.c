


main()
{
	char	*arglist[4];

	arglist[0] = "ls";
	arglist[1] = "/bin";
	arglist[2] = "/etc";
	arglist[3] = 0 ;
	execvp( "gerbil" , arglist );
	perror("gerbil");
}
