INCLUDES = -I../inih -I../simplelogger
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = /usr/local/lib/provenancelib.a ../inih/inih.a ../simplelogger/simplog.a -lpthread -lz

.SUFFIXES: .c

all:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS)

debug:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS) -g

install:
	cp --force ./config.o /usr/bin/camconfigd
	mkdir -p /var/camflow
	cp --force ./camconfigd.service /etc/systemd/system/camconfigd.service
	systemctl enable camconfigd.service

restart:
	systemctl restart camconfigd.service

clean:
	rm -f config.o
