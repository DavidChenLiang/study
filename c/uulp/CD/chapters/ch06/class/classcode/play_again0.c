#include	<stdio.h>
#include	<termios.h>
/* 
 * play_again0.c
 *
 *	purpose: ask if user wants another transaction
 *	 method: ask a question, wait for yes/no answer
 *	returns: 0=>yes, 1=>no
 *	 better: eliminate need to press return 
 */
#define	QUESTION	"Do you want another transaction"

main()
{
	int	response;

	response = get_response(QUESTION);	/* get some answer	*/
	return response;
}
get_response( char *question )
/*
 * purpose: ask a question and wait for a y/n answer
 *  method: use getchar and ignore non y/n answers
 * returns: 0=>yes, 1=>no
 */
{
	int	input;
	printf("%s (y/n)?", question);
	while ( (input = getchar() ) != EOF ) {
		if ( input == 'y' || input == 'Y' )
			return 0;
		if ( input == 'n' || input == 'N' )
			return 1;
	}
}
