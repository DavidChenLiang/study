#
# makefile for bounce2d - sort of like pong, but with no walls or paddle
#

bounce2d: bounce2d.o set_ticker.o
	cc -o bounce2d bounce2d.o set_ticker.o -lcurses

clean:
	rm -f *.o 
