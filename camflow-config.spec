Summary: CamFlow config service
Name: camflow-config
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
cp -f %{SOURCEURL0}/src/config.o ./usr/bin/camflow-config
cp -f %{SOURCEURL0}/src/config.o ./etc/systemd/system/camflow-config.service
cp -f %{SOURCEURL0}/camflow.ini ./etc/camflow.ini
%clean
rm -r -f "$RPM_BUILD_ROOT"

%files
%defattr(755,root,root)
/usr/bin/camflow-config
%defattr(644,root,root)
/etc/systemd/system/camflow-config.service
/etc/camflow.ini
%dir /var/camflow
