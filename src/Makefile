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
	cp --force ./config.o /usr/bin/camflow-config
	mkdir -p /var/camflow
	cp --force ./camflow-config.service /etc/systemd/system/camflow-config.service
	systemctl enable camflow-config.service

restart:
	systemctl restart camflow-config.service

clean:
	rm -f config.o
