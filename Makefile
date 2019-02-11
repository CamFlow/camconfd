version=0.4.4

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

deb:
	sudo alien output/camconfd-$(version)-1.x86_64.rpm
	cp *.deb ./output

publish_rpm:
	cd ./output && package_cloud push camflow/provenance/fedora/27 camconfd-$(version)-1.x86_64.rpm

publish_deb:
	cd ./output && package_cloud push camflow/provenance/ubuntu/bionic camconfd_$(version)-2_amd64.deb

publish: publish_rpm publish_deb
