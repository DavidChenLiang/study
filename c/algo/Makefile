CC=gcc
OBJ=
CFLAGS=-g -Wall
frames:
	$(CC) $(CFLAGS) -o frames frames.c  list.c
ls:
	$(CC) $(CFLAGS) -c list.c
qk:
	$(CC) $(CFLAGS) -o qk directls.c qksort.c issort.c -D QK
is:
	$(CC) $(CFLAGS) -o is directls.c issort.c -D IS
bi:
	$(CC) $(CFLAGS) -o bi spell.c bisearch.c
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf qk is bi ls frames
