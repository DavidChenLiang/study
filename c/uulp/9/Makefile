CC=gcc
CFLAGS=-g3 -Wall
smsh1:splitline.o execute.o
smsh2:splitline.o execute.o process.o controlflow.o
smsh3:splitline.o execute.o process3.o controlflow.o builtin.o varlib.o
smsh4:splitline.o execute2.o process3.o controlflow.o builtin.o varlib.o
getenv:
showenv:
changeenv:
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf getenv showenv changeenv smsh1 smsh2 smsh3 smsh4
