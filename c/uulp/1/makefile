CC=gcc
OBJ=more01.o more02.o more03.o cp1.o
more:more01 more02 more03
more01:more01.o
	$(CC) -o $@ $^
more02:more02.o
	$(CC) -o $@ $^
more03:more03.o
	$(CC) -o $@ $^
cp1:cp1.o
	$(CC) -o $@ $^
cp2:cp2.o
	$(CC) -o $@ $^
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf more01 more02 more03
	-rm -rf cp1 cp2 
