# Copyright (C) 2021-2026 - Soroush Rabiei, <soroush.rabiei@gmail.com>
# This file is part of libcalendars.
#
# libcalendars is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libcalendars is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.

# Keep in step with the SOVERSION set in lib/CMakeLists.txt. The runtime
# package is named after it, so a change here without a rename is a bug.
%global sover 1

# The buildroot policy strips static archives, which leaves the shipped
# libcalendars.a with no debug information and nothing to recover it from,
# since a static library gets no debuginfo package of its own. Turning the
# policy off keeps the debug output that the distribution build flags already
# ask for.
%global __brp_strip_static_archive %{nil}

Name:           libcalendars
Version:        1.1.0
Release:        1%{?dist}
Summary:        Precise calendar arithmetic library

License:        GPL-3.0-or-later
URL:            https://github.com/soroush/libcalendars
Source0:        %{url}/archive/v%{version}/%{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  gcc
BuildRequires:  make

%description
A precise C library providing arithmetic for the most common calendar
systems. Gregorian, Julian, Milankovic, Solar Hijri (also known as Shamsi
or Jalali), Islamic Civil, Jewish (also known as Hebrew), Egyptian and
Babylonian calendar systems are provided.

Conversions run through Julian Day Numbers, and the library operates on
plain integers rather than introducing date structures of its own, so that
it can be used behind an existing date and time API.

%package devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description devel
Header files, the pkg-config file and the CMake package configuration
needed to build applications against %{name}.

%package static
Summary:        Static library for %{name}
Requires:       %{name}-devel%{?_isa} = %{version}-%{release}

%description static
The %{name} library built for static linking. Applications that link it
must be rebuilt and shipped again whenever %{name} is updated, so prefer
the shared library unless static linking is required.

%prep
%autosetup

%build
%cmake -DBUILD_TESTING:BOOL=ON -DLIBCALENDARS_GIT_HOOKS:BOOL=OFF
%cmake_build

%install
%cmake_install

%check
%ctest

%files
%license COPYING
%doc README.md
%{_libdir}/%{name}.so.%{sover}
%{_libdir}/%{name}.so.%{version}

%files devel
%{_includedir}/libcalendars/
%{_libdir}/%{name}.so
%{_libdir}/pkgconfig/%{name}.pc
%{_libdir}/cmake/libcalendars/

%files static
%{_libdir}/%{name}.a

%changelog
* Wed Aug 19 2026 Soroush Rabiei <soroush.rabiei@gmail.com> - 1.1.0-1
- Rewrite the spec for the CMake build. The previous one drove autotools.
- Drop BuildRoot, Group, %%clean and the ldconfig scriptlets, none of which
  are used any more.
- Move the license tag to the SPDX identifier GPL-3.0-or-later.
- Split the static library into its own subpackage.
- Run the test suite in %%check.

* Tue Nov 20 2018 Soroush Rabiei <soroush.rabiei@gmail.com> - 1.0.0-1
- Initial package files for the library (release 1)
