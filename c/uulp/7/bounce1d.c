/*
 * =====================================================================================
 *
 *       Filename:  bounce1d.c
 *
 *    Description:  for bounce 1 demo
 *
 *        Version:  1.0
 *        Created:  2015年02月07日 15时32分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <signal.h>

#define  MESSAGE "Hello"
#define  BLANK   "     "

nt
main(void)
{
    int delay;
    int ndelay;
    int c;
    void move_msg(int);
    int set_ticker(int);

    initscr();
    crmode();
    noecho();
    clear();

    int ROW;
    int col;
    int dir;

    row = 10;
    col = 0;
    dir = 1;
    delay = 200;

    move(ROW,col);
    addstr(MESSAGE);
    signal(SIGALRM,move_msg);
    set_ticker(delay);

    while(1)
    {
	ndelay = 0;
	c = getchar();
	if (c == 'Q') break;
	if (c == ' ')dir = -dir;
	if (c == 'f' && delay > 2) ndelay = delay/2;
	if (c == 's') ndelay = delay * 2;
	if (ndelay > 0)
	    set_ticker(delay = ndelay);
    }
    endwin();
    return 0;
}
void move_msg(int signum)
{
    signal(SIGALRM,move_msg);
    move(ROW, col);
    addstr(BLANK);
    col += dir;
    move(ROW, col);
    addstr(MESSAGE);
    refresh();
    if (dir == -1 && col <= 0) dir = 1;
    if (dir == +1 && col + strlen(MESSAGE) >= COLS) dir = -1;
}
