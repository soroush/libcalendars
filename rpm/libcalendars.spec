%define name libcalendars
%define version 1.0.0
%define release 1

Name:           %{name}
Version:        %{version}
Release:        %{release}%{?dist}
License:        GPLv3
URL:            https://github.com/soroush/libcalendars
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Summary:        A calendar arithmetic library
Group:          Development/Libraries

BuildRequires: gcc
BuildRequires: libtool
BuildRequires: make

%package devel
Summary:        Development files for using ${name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       pkgconfig
Provides:       %{name}-devel = %{version}-%{release}

%description
A precise C library to provide arithmentic for the most common
calendar systems. Currently Gregorian, Julian, Milankovic, Solar
Hijri (also known as Shamsi or Jalali), Islamic Civil and
Jewish (also know as Hebrew) calendar systems are provided.


%description devel
This package contain development files for ${name}. It should be
installed if you want to develop programs that will use the ${name}
library.

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%{_libdir}/*.so.*
%exclude %{_libdir}/*.a*
%exclude %{_libdir}/*.la*
%exclude %{_libdir}/pkgconfig/*
%exclude %{_includedir}/*

%files devel
%{_libdir}/*.so
%{_libdir}/*.a*
%{_libdir}/*.la*
%{_libdir}/pkgconfig/*
%{_includedir}/*
%exclude %{_libdir}/*.so.*

%changelog
* Tue Nov 20 2018 Soroush Rabiei <soroush.rabiei@gmail.com> 1.0-1
- Initial package files for the library (release 1)
