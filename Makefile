version=0.3.1

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

rpm:
	mkdir -p ~/rpmbuild/{RPMS,SRPMS,BUILD,SOURCES,SPECS,tmp}
	cp -f ./camconfigd.spec ~/rpmbuild/SPECS/camconfigd.spec
	rpmbuild -bb camconfigd.spec
	mkdir -p output
	cp ~/rpmbuild/RPMS/x86_64/* ./output

publish:
	cd ./output && package_cloud push camflow/provenance/fedora/25 camconfigd-$(version)-1.x86_64.rpm
