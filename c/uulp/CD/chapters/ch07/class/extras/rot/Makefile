# Simple makefile for rot program
# for that bloody stupid System V Make
SHELL=/bin/sh

CFLAGS = -O -DSYSV

rot:	rot.c
	cc $(CFLAGS) -o rot rot.c -lcurses

rot.shar: Makefile rot.c
	shar >rot.shar Makefile rot.c
