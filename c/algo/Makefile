CC=gcc
OBJ=
CFLAGS=-g -Wall
QK:
	$(CC) $(CFLAGS) -o main directls.c qksort.c issort.c -D QK
IS:
	$(CC) $(CFLAGS) -o main directls.c issort.c -D IS
BI:
	$(CC) $(CFLAGS) -o bi spell.c bisearch.c
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf main bi
