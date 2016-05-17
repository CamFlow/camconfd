all:
	cd ./src && $(MAKE) all

clean:
	cd ./ifclib && $(MAKE) clean
	cd ./inih && $(MAKE) clean
	cd ./provenancelib && $(MAKE) clean
	cd ./src && $(MAKE) clean

prepare:
	cd ./ifclib && $(MAKE) prepare
	cd ./inih && $(MAKE) prepare
	cd ./provenancelib && $(MAKE) prepare
	cd ./ifclib && $(MAKE) all
	cd ./inih && $(MAKE) all
	cd ./provenancelib && $(MAKE) all

install:
	cd ./src && sudo $(MAKE) install
