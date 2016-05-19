INCLUDES = -I../ifclib -I../inih -I../provenancelib -I../simplelogger
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = ../provenancelib/provenancelib.a ../ifclib/ifclib.a ../inih/inih.a ../simplelogger/simplog.a -lpthread

.SUFFIXES: .c

all:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS)

debug:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS) -g

install:
	cp --force ./config.o /usr/bin/camflow-config
	mkdir -p /var/camflow
	cp --force ./camflow-config.service /etc/systemd/system/camflow-config.service
	systemctl enable camflow-config.service

clean:
	rm -f config.o
