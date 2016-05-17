GIT_SOURCE=https://github.com/CamFlow/camflow-ifc-lib.git

all:
	cd ./build && $(MAKE) all
	cp --force ./build/src/ifclib.a ./ifclib.a

clean:
	rm -f ifclib.a

prepare:
	mkdir -p build
	cd ./build && git init && git remote add origin $(GIT_SOURCE) && git fetch origin && git checkout -b master --track origin/master
	cp --force ./build/include/ifclib.h ./ifclib.h
	cd ./build && $(MAKE) prepare
