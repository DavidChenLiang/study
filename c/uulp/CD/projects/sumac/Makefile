#
# makefile for popsh
#
# popsh is a simple interface to a pop server
# it does the login dialog and it knows when to expect
# multi-line replies and when to expect one-line replies
#

CC = gcc 

popsh: popsh.o servconn.o socklib.o
	cc -o popsh popsh.o servconn.o socklib.o
