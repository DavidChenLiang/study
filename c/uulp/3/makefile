CC=gcc
OBJ=ls1.o 
ls1:ls1.o
	$(CC) -o $@ $^
filesize:filesize.o
	$(CC) -o $@ $^
fileinfo:fileinfo.o
	$(CC) -o $@ $^
.PHONY:clean
clean:
	-rm -rf *.o
	-rm ls1 
	-rm filesize
	-rm fileinfo
