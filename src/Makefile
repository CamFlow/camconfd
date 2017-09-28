INCLUDES = -I../inih
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = -lprovenance ../inih/inih.a -lpthread -lz

.SUFFIXES: .c

all:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS)

debug:
	$(CCC) $(INCLUDES) config.c $(LIB) -o config.o $(CCFLAGS) -g

install:
	cp --force ./config.o /usr/bin/camconfd
	mkdir -p /var/camflow
	cp --force ./camconfd.service /etc/systemd/system/camconfd.service
	systemctl enable camconfd.service

restart:
	systemctl restart camconfd.service

clean:
	rm -f config.o
