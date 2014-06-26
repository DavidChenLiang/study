CC=gcc
CFLAGS=-g3 -Wall
OBJ=
hello1:
	$(CC) $(CFLAGS) hello1.c -o hello1 -lncurses
hello2:
	$(CC) $(CFLAGS) hello2.c -o hello2 -lncurses
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf hello1 hello2
