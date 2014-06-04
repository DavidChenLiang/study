
main()
{
	printf("before fork, my pid is %d\n" , getpid());
	fork();
	fork();
	fork();
	printf("done, my pid is %d\n", getpid());
}
