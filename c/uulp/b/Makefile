CC=gcc
CFLAGS=-g3 -Wall
OBJS=splitline.o execute.o showenv.o changeenv.o process.o controlflow.o
smsh1:splitline.o execute.o
smsh2:splitline.o execute.o process.o controlflow.o
getenv:
showenv:
changeenv:
.PHONY:clean
clean:
	-rm -rf $(OBJS)
	-rm -rf getenv showenv changeenv 
	-rm -rf smsh1
	-rm -rf smsh2
