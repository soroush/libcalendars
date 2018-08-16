# Copyright 2017 - Soroush Rabiei, <soroush@ametisco.ir>
# This file is part of libcalendar.
#
# libcalendar is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libcalendar is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libcalendar.  If not, see <http://www.gnu.org/licenses/>.

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(srcdir)/..
AM_CXXFLAGS = --pedantic -Wall -Werror

LDADD = \
    ../src/libcalendars.la

check_PROGRAMS = \
    tst_gregorian \
    tst_julian \
    tst_milankovic \
    tst_jewish \
    tst_solar_hijri \
    tst_islamic_civil

tst_solar_hijri_SOURCES = \
    tst-common.h \
    tst-common.c \
    tst-solar-hijri.c

tst_gregorian_SOURCES = \
    tst-common.h \
    tst-common.c \
    tst-gregorian.c

tst_julian_SOURCES = \
    tst-common.h \
    tst-common.c \
    tst-julian.c

tst_milankovic_SOURCES = \
    tst-common.h \
    tst-common.c \
    tst-milankovic.c


tst_jewish_SOURCES = \
    tst-common.h \
    tst-common.c \
    tst-jewish.c

tst_islamic_civil_SOURCES = \
    tst-common.h \
    tst-common.c \
    tst-islamic-civil.c

TESTS = $(check_PROGRAMS)
