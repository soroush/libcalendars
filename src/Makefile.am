# Copyright 2017 - Soroush Rabiei, <soroush@ametisco.ir>
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

libcalendars_includedir = $(includedir)/libcalendars
libcalendars_include_HEADERS =  \
    cl-calendars.h \
    cl-export.h \
    cl-gregorian.h \
    cl-julian.h \
    cl-milankovic.h \
    cl-solar-hijri.h \
    cl-islamic-civil.h \
    cl-jewish.h

lib_LTLIBRARIES = libcalendars.la
libcalendars_la_LDFLAGS = -version-info $(LIBCALENDAR_SO_VERSION)
libcalendars_la_SOURCES = \
    $(libcalendars_include_HEADERS) \
    cl-tz.h \
    cl-math.h \
    cl-math.c \
    cl-calendars.c \
    cl-gregorian.c \
    cl-julian.c \
    cl-milankovic.c \
    cl-solar-hijri.c \
    cl-islamic-civil.c \
    cl-jewish.c

libcalendars_la_LIBADD = \
    -lm
