#
# makefile for lecture 2
#

who1: who1.c
	cc -o who1 who1.c

who2: who2.c
	cc -o who2 who2.c

who3: who3.o utmplib.o
	cc -o who3 who3.o utmplib.o

llcopy: llcopy.c
	cc llcopy.c -o llcopy

#
# tests if llcopy works like cp
#
copytest: llcopy
	ls -l /bin > data
	./llcopy data data.copy
	@if diff data data.copy ; then echo sucess ; else echo error ; fi
