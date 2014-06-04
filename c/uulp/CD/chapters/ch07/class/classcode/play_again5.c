#include	<stdio.h>
#include	<curses.h>
#include	<signal.h>

/* 
 * play_again5.c
 *
 *	purpose: ask if user wants another transaction
 *	 method: use curses to select crmode() and noecho()
 *		 uses set_ticker() to send pulses
 *	returns: 0=>yes, 1=>no, 2=>timeout
 *	   note: requires alarmlib.o -lcurses
 */
#define	ASK		"Do you want another transaction"
#define	TIMEOUT	   	5	/* in seconds	*/

main()
{
	int	response;

	initscr();
	crmode();
	noecho();
	clear();
	response = get_response(ASK, TIMEOUT);	/* get some answer	*/
	endwin();
	return response;
}

int	time_left = 0;

get_response( question , timeout )
char *question;
/*
 * purpose: ask a question and wait for a y/n answer or timeout
 *  method: set ticker to generate question marks
 * returns: 0=>yes, 1=>no
 */
{
	int	input;
	void	alarm_handler();

	time_left = timeout;			/* set global var	*/
	signal( SIGALRM, alarm_handler );	/* set handler		*/
	set_ticker(1000);			/* and ticker		*/

	move(LINES/2, 10);
	addstr( question );
	addstr( " (y/n)? " );
	refresh();
	while ( time_left > 0 ){
		input = getch();			/* use curseses	*/
		if ( input == 'y' || input == 'Y' )	/* Y? 		*/
			return 0;
		if ( input == 'n' || input == 'N' )	/* N?		*/
			return 1;
	}
	return 2;
}

void
alarm_handler()
{
	signal(SIGALRM, alarm_handler);			/* reset trap	*/
	addch('?');					/* prompt user	*/
	refresh();					/* and show it	*/
	time_left--;					/* adjust count	*/
	if ( time_left == 0 )
	{
		endwin();
		exit(2);
	}
}
