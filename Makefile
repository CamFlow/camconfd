all:
	cd ./src && $(MAKE) all

clean:
	cd ./src && $(MAKE) clean

prepare:
	cd ./inih && $(MAKE) prepare
	cd ./simplelogger && $(MAKE) prepare
	cd ./inih && $(MAKE) all
	cd ./simplelogger && $(MAKE) all

install:
	cd ./src && sudo $(MAKE) install
	sudo cp --force ./camflow.ini /etc/camflow.ini

restart:
	cd ./src && sudo $(MAKE) restart
