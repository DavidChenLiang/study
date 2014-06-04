


main(int ac, char *av[])
{
	char	*arglist[4];

	printf("hi, this is exec2.  My process ID number is %d\n", getpid());
	printf("My argument is is %s %s %s\n", av[0],av[1], av[2]);
	arglist[0] = "ls";
	arglist[1] = "/bin";
	arglist[2] = "/etc";
	arglist[3] = 0 ;
	execvp( "exec2" , arglist );
}
