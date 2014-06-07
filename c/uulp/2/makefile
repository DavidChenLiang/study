CC=gcc
OBJ=who1.o 
who:who1 who2  
who1:who1.o
	$(CC) -o $@ $^
who2:who2.o
	$(CC) -o $@ $^
.PHONY:clean
clean:
	-rm -rf *.o
	-rm who1 
