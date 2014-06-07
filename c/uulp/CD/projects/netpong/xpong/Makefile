#
# you may need to adjust these settings for your system
#
IFLAG=-I/usr/X11R6/include
LFLAG=-L/usr/X11R6/lib

pong: alarmlib.o pong.o
	cc -o pong $(LFLAG) -lX11 alarmlib.o pong.o

alarmlib.o: alarmlib.c
	cc $(IFLAG) -c alarmlib.c

pong.o: pong.c pong.h
	cc $(IFLAG) -c pong.c

clean:
	rm -f *.o pong
