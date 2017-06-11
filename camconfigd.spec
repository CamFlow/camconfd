Summary: CamFlow config service
Name: camconfigd
Version: 0.3.1
Release: 1
Group: audit/camflow
License: GPLv3
Source: %{expand:%%(pwd)}
BuildRoot: %{_topdir}/BUILD/%{name}-%{version}-%{release}

%description
%{summary}

%prep
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/bin
mkdir -p $RPM_BUILD_ROOT/etc/systemd/system
mkdir -p $RPM_BUILD_ROOT/var/camflow
cd $RPM_BUILD_ROOT
cp -f %{SOURCEURL0}/src/config.o ./usr/bin/camconfigd
cp -f %{SOURCEURL0}/src/camconfigd.service ./etc/systemd/system/camconfigd.service
cp -f %{SOURCEURL0}/camflow.ini ./etc/camflow.ini
%clean
rm -r -f "$RPM_BUILD_ROOT"

%files
%defattr(755,root,root)
/usr/bin/camconfigd
%defattr(644,root,root)
/etc/systemd/system/camconfigd.service
/etc/camflow.ini
%dir /var/camflow
