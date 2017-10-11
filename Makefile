version=0.3.5

all:
	cd ./src && $(MAKE) all

clean:
	cd ./src && $(MAKE) clean

prepare:
	cd ./inih && $(MAKE) prepare
	cd ./inih && $(MAKE) all

install:
	cd ./src && sudo $(MAKE) install
	sudo cp --force ./camflow.ini /etc/camflow.ini

restart:
	cd ./src && sudo $(MAKE) restart

rpm:
	mkdir -p ~/rpmbuild/{RPMS,SRPMS,BUILD,SOURCES,SPECS,tmp}
	cp -f ./camconfd.spec ~/rpmbuild/SPECS/camconfd.spec
	rpmbuild -bb camconfd.spec
	mkdir -p output
	cp ~/rpmbuild/RPMS/x86_64/* ./output

publish:
	cd ./output && package_cloud push camflow/provenance/fedora/26 camconfd-$(version)-1.x86_64.rpm
