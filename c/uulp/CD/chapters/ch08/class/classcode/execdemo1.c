
main()
{
	char *args[4];

	args[0] = "ls";			/* build the arglist */
	args[1] = "-l";
	args[2] = "/usr/bin";
	args[3] = (char *) 0;		/* terminate with NULL */

	printf("about to execute ls -l /usr/bin\n" );
	execvp( "ls" , args );
	printf( "that was ls, cool, eh?\n");
}

