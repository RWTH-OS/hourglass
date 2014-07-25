
CC=gcc
CFLAGS=-O2
LDFLAGS=
LIBS=

default : hg

hg : main.o opt.o init.o setup.o run.o report.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ 

