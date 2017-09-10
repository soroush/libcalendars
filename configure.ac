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

AC_PREREQ([2.69])
AC_INIT([libcalendar], [1.0.0])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_INIT([static shared pic-only])

# Configure automake
AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

# Checks for libraries.
AC_CHECK_LIB([m], [floor])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([floor modf])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile
                 libcalendar.pc])

AC_SUBST([LIBCALENDAR_SO_VERSION], [1:0:0])
AC_SUBST([LIBCALENDAR_API_VERSION], [1.0.0])

AC_OUTPUT
