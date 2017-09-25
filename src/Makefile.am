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

AM_CPPFLAGS = \
    -DLIBCALENDAR_EXPORT

AM_CFLAGS = \
    --pedantic \
    -Wall -Werror -Wno-unused-parameter -Wno-unused-function \
    -Wno-unused-label -Wpointer-arith -Wformat -Wreturn-type \
    -Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self \
    -Wuninitialized -Wno-deprecated -Wformat-security \
    -fvisibility=hidden -fPIC -fno-exceptions -fstack-protector \
    -Wl,-z,relro -Wl,-z,now -Wl,--no-undefined -Wl,--discard-all \
    -Wl,--build-id=sha1 -rdynamic

libcalendar_includedir = $(includedir)/calendar
libcalendar_include_HEADERS =  \
    cl-math.h \
    cl-export.h \
    cl-gregorian.h \
    cl-julian.h \
    cl-milankovic.h \
    cl-solar-hijri.h \
    cl-jewish.h

lib_LTLIBRARIES = libcalendar.la
libcalendar_la_LDFLAGS = -version-info $(LIBCALENDAR_SO_VERSION)
libcalendar_la_SOURCES = \
    $(libcalendar_include_HEADERS) \
    cl-math.c \
    cl-gregorian.c \
    cl-julian.c \
    cl-milankovic.c \
    cl-solar-hijri.c \
    cl-jewish.c

libcalendar_la_LIBADD = \
    -lm
