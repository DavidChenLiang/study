#include	<stdio.h>

/*
 * popen_ex3.c
 *	shows how to use popen to write to a process that
 *	reads from stdin.  This program writes email to
 *	two users.  Note how easy it is to use fprintf
 *	to format the data to send.
 */

main()
{
	FILE	*fp;

	fp = popen( "mail user1 user2", "w" );
	fprintf( fp, "hello...how are you?\n" );
	pclose( fp );
}
