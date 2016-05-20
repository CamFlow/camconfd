all:
	cd ./ifclib && $(MAKE) all
	cd ./inih && $(MAKE) all
	cd ./provenancelib && $(MAKE) all
	cd ./simplelogger && $(MAKE) all
	cd ./src && $(MAKE) all

clean:
	cd ./ifclib && $(MAKE) clean
	cd ./inih && $(MAKE) clean
	cd ./provenancelib && $(MAKE) clean
	cd ./simplelogger && $(MAKE) clean
	cd ./src && $(MAKE) clean

prepare:
	cd ./ifclib && $(MAKE) prepare
	cd ./inih && $(MAKE) prepare
	cd ./provenancelib && $(MAKE) prepare
	cd ./simplelogger && $(MAKE) prepare

install:
	cd ./src && sudo $(MAKE) install
	sudo cp --force ./camflow.ini /etc/camflow.ini
