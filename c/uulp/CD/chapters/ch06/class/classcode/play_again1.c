#include	<stdio.h>
#include	<termios.h>
/* 
 * play_again1.c
 *
 *	purpose: ask if user wants another transaction
 *	 method: set tty into char-by-char mode, read char, return result
 *	returns: 0=>yes, 1=>no
 *	 better: do no echo inappropriate input
 */
#define	QUESTION	"Do you want another transaction"

main()
{
	int	response;

	set_crmode();				/* set chr-by-chr mode	*/
	response = get_response(QUESTION);	/* get some answer	*/
	reset_tty_mode();			/* restore tty state	*/
	return response;
}
get_response( char *question )
/*
 * purpose: ask a question and wait for a y/n answer
 *  method: use getchar and complain about non-y/n input
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
		printf("\ncannot understand %c, Please type y or no\n",input);
	}
}

struct termios	original_mode;		/* used by restore	*/

set_crmode()
/* 
 * purpose: put file descriptor 0 (i.e. stdin) into chr-by-chr mode
 *  method: use bits in termios
 */
{
	struct	termios	ttystate;

	tcgetattr( 0, &ttystate);		/* read curr. setting	*/
	original_mode   	= ttystate;	/* remember these	*/
	ttystate.c_lflag        &= ~ICANON;	/* no buffering		*/
	ttystate.c_cc[VMIN]     =  1;		/* get 1 char at a time	*/
	tcsetattr( 0 , TCSANOW, &ttystate);	/* install settings	*/
}

reset_tty_mode()
{
	tcsetattr(0, TCSANOW, &original_mode);	/* put back orig mode	*/
}
