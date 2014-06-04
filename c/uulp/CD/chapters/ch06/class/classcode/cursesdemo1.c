#include	<stdio.h>
#include	<curses.h>

main()
{
	initscr();
	clear();
	move(10,20);
	addstr("hello, world");
	move(0,0);
	refresh();
	endwin();
}
