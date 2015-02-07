CC=gcc
CFLAGS=-g3 -Wall
OBJ=
hello1:
	$(CC) $(CFLAGS) hello1.c -o hello1 -lncurses
hello2:
	$(CC) $(CFLAGS) hello2.c -o hello2 -lncurses
hello3:
	$(CC) $(CFLAGS) hello3.c -o hello3 -lncurses
hello4:
	$(CC) $(CFLAGS) hello4.c -o hello4 -lncurses
hello5:
	$(CC) $(CFLAGS) hello5.c -o hello5 -lncurses
	
sleep1:
	$(CC) $(CFLAGS) sleep1.c -o sleep1 
	
ticker_demo:
	$(CC) $(CFLAGS) ticker_demo.c -o ticker_demo 
	
sigdemo3:
	$(CC) $(CFLAGS) sigdemo3.c -o sigdemo3 

sigactdemo:
	$(CC) $(CFLAGS) sigactdemo.c -o sigactdemo 

bounce1d:
	$(CC) $(CFLAGS) bounce1d.c set_ticker.c -o bounce1d -lncurses

bounce2d:
	$(CC) $(CFLAGS) bounce2d.c set_ticker.c -o bounce2d -lncurses
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf hello1 hello2 hello3 hello4 hello5 sleep1 ticker_demo sigdemo3 sigactdemo bounce1d bounce2d
