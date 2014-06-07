CC=gcc
OBJ=hello1.o
hello1:$(OBJ)
	$(CC) -o $@ -lncurses
hello2:hello2.o
	$(CC) -o $@ -lncurses 
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf hello1 hello2
