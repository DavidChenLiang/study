CC=gcc
OBJ=who1.o 
CFLAGS=-g3 -Wall
who:who1 who2  
who1:who1.o
	$(CC) ${CFLAGS} -o $@ $^
who2:who2.o
	$(CC) ${CFLAGS} -o who2  who2.c

cp1:
	$(CC) ${CFLAGS} -o cp1  cp1.c
.PHONY:clean
clean:
	-rm -rf *.o
	-rm who1 who2 cp1
