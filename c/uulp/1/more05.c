#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>



#define MOVE_TO_DOWN_LEFT_CORNER() printf("\033[42;0H")
#define CLEAN_LINE() printf("\033[K")
int ROW;
int COL;

void do_more(FILE *);
void rowCol();


int
main(int argc, char **argv)
{
    
    FILE *fp;
    tty_mode(0);
    rowCol();
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
rowCol(){
// stty -size 42 106
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
    int c;
    printf("\033[7m--more--\033[m");
    printf("\033[?25l");
    while ((c = getc(cmd)) != EOF){
        if (c == 'q')
		return 0;
	if (c == ' ')
		return ROW;
	if (c == '\n')
		return 1;
    }
    return 0;
}

tty_mode(int how)
{
    static struct termios original_mode;
    if (how == 0)
        tcgetattr(0,&original_mode);
    else
        return tcsetattr(0,TCSANOW, &original_mode);
}

set_cr_noecho_mode()
{
    struct termios    ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag    &=  ~ICANON;
    ttystate.c_lflag    &=  ~ECHO;
    ttystate.c_cc[VMIN]  = 1;
    tcsetattr(0,TCSANOW,&ttystate);
}
