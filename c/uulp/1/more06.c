#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <curses.h>



#define MOVE_TO_DOWN_LEFT_CORNER() printf("\033[%d;0H",ROW)
#define CLEAN_LINE() printf("\033[K")
#define CONCEAL_CURSOR() printf("\033[?25l")
int ROW;
int COL;

void do_more(FILE *);
void setRowCol();
void tty_mode(int);
void set_cr_noecho_mode();



int
main(int argc, char **argv)
{
    
    FILE *fp;
    tty_mode(0);
    setRowCol();
    if (argc == 1){
        do_more(stdin);
    }else{
        set_cr_noecho_mode();
        while(--argc){
	    if ((fp = fopen(*++argv,"r")) != NULL){
	        do_more(fp);
		    fclose(fp);
	    }else{
	        exit(1);
	    }//if
	}//while
    }
    tty_mode(1);
    return 0;
}

void 
setRowCol(){
	//you can also run stty -size to get the information 
	//ie., stty -size 
	//return 42 106
        struct winsize size;
	ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
	ROW = size.ws_row;
	COL = size.ws_col;
}

void
do_more(FILE *fp){
    char line[COL];
    int num_of_lines = 0;
    int see_more(FILE *),reply;
    FILE * fp_tty;
    fp_tty = fopen("/dev/tty","r");
    if (fp_tty == NULL)
        exit(1);

    
    while(fgets(line,COL, fp)){
        if (num_of_lines == ROW){
	    reply = see_more(fp_tty);
	    if (reply == 0)
		   {
                       printf("\n");
                       break;
                   }
	    num_of_lines -= reply;
	}//if
	MOVE_TO_DOWN_LEFT_CORNER();
	CLEAN_LINE();
	if (fputs(line, stdout) == EOF)
		exit(1);

	num_of_lines++;
    }//while
}

int 
see_more(FILE * cmd){
    struct winsize wbuf;
    if (ioctl(0,TIOCGWINSZ,&wbuf) == -1){
	    perror("ioctl error");
    }
    printf("\033[7m--more--() Rows:%d Columns:%d Xpixel:%d Ypixel:%d\033[m",
		                  wbuf.ws_row, 
				  wbuf.ws_col,
				  wbuf.ws_xpixel,
				  wbuf.ws_ypixel);
    //CONCEAL_CURSOR();
    int c;
    while ((c = getc(cmd)) != EOF){
        if (c == 'q')
		return 0;
	if (c == ' ')
//		return ROW;
		return LINES;
	if (c == '\n')
		return 1;
    }
    return 0;
}

void
tty_mode(int how)
{
    static struct termios original_mode;
    if (how == 0)
        tcgetattr(0,&original_mode);
    else
        tcsetattr(0,TCSANOW, &original_mode);
}

void
set_cr_noecho_mode()
{
    struct termios    ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag    &=  ~ICANON;
    ttystate.c_lflag    &=  ~ECHO;
    ttystate.c_cc[VMIN]  = 1;
    tcsetattr(0,TCSANOW,&ttystate);
}
