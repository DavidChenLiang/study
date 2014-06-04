#include <curses.h>

/*
 * demo of using clearok to recover the screen after running
 * and external program
 *
 * compile this with:  cc clearokdemo.c -lcurses -o clearokdemo
 */

main()
{
	initscr();
	clear();
	mvaddstr(10,20,"hello");
	refresh();
	sleep(5);
	reset_shell_mode();
	system("/bin/sh");
	reset_prog_mode();
	clearok(stdscr,TRUE);
	refresh();
	getch();
	endwin();
}
