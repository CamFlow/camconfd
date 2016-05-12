all:
	cd ./inih && $(MAKE) all
	cd ./src && $(MAKE) all

clean:
	cd ./inih && $(MAKE) clean
	cd ./src && $(MAKE) clean

prepare:
	cd ./inih && $(MAKE) prepare

install:
	cd ./src && sudo $(MAKE) install
