GIT_SOURCE=https://github.com/CamFlow/camflow-audit-lib.git

all:
	cd ./build && $(MAKE) all
	cp --force ./build/src/provenancelib.a ./provenancelib.a

clean:
	rm -f provenancelib.a

prepare:
	mkdir -p build
	cd ./build && git init && git remote add origin $(GIT_SOURCE) && git fetch origin && git checkout -b master --track origin/master
	cp --force ./build/include/provenancelib.h ./provenancelib.h
	cd ./build && $(MAKE) prepare
