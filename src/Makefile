
#CC=color-gcc
CC=gcc
CFLAGS=  #-O2  -Wall -Wextra -Wno-unused-parameter -g
LDFLAGS=
LIBS=-lm

PROGRAM=hg
CFILES=$(shell ls *.c)
HFILES=$(shell ls *.h)
OFILES=$(CFILES:.c=.o)

default : $(PROGRAM)

quick : $(PROGRAM)

$(PROGRAM) : $(OFILES)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ 

.depend : $(CFILES) $(HFILES)
	$(CC) -MM $(CFILES) > $@

-include .depend

.PHONY : default

tags :
	ctags -R

clean :
	-rm -f *.o $(PROGRAM) .depend

