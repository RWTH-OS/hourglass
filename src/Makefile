
CC=gcc
CFLAGS=-O2
LDFLAGS=
LIBS=

PROGRAM=hg
CFILES=$(shell ls *.c)
HFILES=$(shell ls *.h)
OFILES=$(CFILES:.c=.o)

default : $(PROGRAM)

$(PROGRAM) : main.o opt.o init.o setup.o run.o report.o rdtsc.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ 

.depend : $(CFILES) $(HFILES)
	$(CC) -MM $(CFILES) > $@

-include .depend

.PHONY : default

tags :
	ctags -R

clean :
	-rm -f *.o $(PROGRAM) .depend
	-rm -f svn.version svn.h svnversion.out

