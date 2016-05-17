INCLUDES = -I../ifclib -I../inih -I../provenancelib
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = ../provenancelib/provenancelib.a ../ifclib/ifclib.a ../inih/inih.a -lpthread

.SUFFIXES: .c

all:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS)

debug:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS) -g

install:

clean:
	rm -f config.o
