#
# you may need to adjust these settings for your system
#
IFLAG=-I/usr/X11R6/include
LFLAG=-L/usr/X11R6/lib

xbounce: alarmlib.o xbounce.o
	cc -o xbounce $(LFLAG) -lX11 alarmlib.o xbounce.o

alarmlib.o: alarmlib.c
	cc $(IFLAG) -c alarmlib.c

xbounce.o: xbounce.c
	cc $(IFLAG) -c xbounce.c

clean:
	rm -f *.o xbounce
