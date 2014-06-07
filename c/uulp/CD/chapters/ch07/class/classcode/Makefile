#
# this is a makefile
# it is a file that describes how 
# to build particular programs
#
# each of the buildable programs has
# a list of components and a list of commands
# Once the components are prepared, the 
# commands are executed
#

bounce2d: bounce2d.o alarmlib.o bounce.h
	cc -o bounce2d bounce2d.o alarmlib.o -lcurses

bounce2d.o: bounce2d.c
	cc -c bounce2d.c

bounce1d: bounce1d.o alarmlib.o bounce.h
	cc -o bounce1d bounce1d.o alarmlib.o -lcurses

bounce1d.o: bounce1d.c
	cc -c bounce1d.c

hello1: hello1.c
	cc hello1.c -lcurses -o hello1

hello2: hello2.c
	cc hello2.c -lcurses -o hello2

hello3: hello3.c
	cc hello3.c -lcurses -o hello3

hello4: hello4.c
	cc hello4.c -lcurses -o hello4

hello5: hello5.c
	cc hello5.c -lcurses -o hello5

hello6: hello6.o alarmlib.o
	cc hello6.o alarmlib.o -lcurses -o hello6

hello6.o: hello6.c
	cc -c hello6.c

alarmlib.o: alarmlib.c
	cc -c alarmlib.c

