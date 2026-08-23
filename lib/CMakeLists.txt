# Copyright (C) 2017-2026 Soroush Rabiei <soroush.rabiei@gmail.com>
#
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
# along with libcalendars.  If not, see <https://www.gnu.org/licenses/>.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16.0)

# Included up here because the install directory variables it defines are
# referenced by the export interface below, not only by the install rules.
include(GNUInstallDirs)

set(CALENDARS_HEADERS
    "include/libcalendars/cl-calendars.h"
    "include/libcalendars/cl-export.h"
    "include/libcalendars/cl-gregorian.h"
    "include/libcalendars/cl-islamic-civil.h"
    "include/libcalendars/cl-jewish.h"
    "include/libcalendars/cl-julian.h"
    "include/libcalendars/cl-milankovic.h"
    "include/libcalendars/cl-solar-hijri.h"
    "include/libcalendars/cl-egyptian.h"
    "include/libcalendars/cl-babylonian.h"
)

set(CALENDARS_SOURCES
    "src/cl-math.h"
    "src/cl-math.c"
    "src/cl-calendars.c"
    "src/cl-gregorian.c"
    "src/cl-julian.c"
    "src/cl-milankovic.c"
    "src/cl-solar-hijri.c"
    "src/cl-islamic-civil.c"
    "src/cl-jewish.c"
    "src/cl-egyptian.c"
    "src/cl-babylonian.c"
)

if(WIN32)
    set(PLATFORM_SOURCES win32/libcalendars.rc)
else()
    set(PLATFORM_SOURCES "")
endif()

# The shared and the static library are compiled separately rather than sharing
# an OBJECT library: on Windows the two need opposite settings of the
# libcalendars_EXPORTS / libcalendars_STATIC pair, so one set of objects cannot
# serve both.

# Define the shared library
add_library(calendars SHARED
    ${CALENDARS_HEADERS}
    ${CALENDARS_SOURCES}
    ${PLATFORM_SOURCES}
)

# Define the static library
add_library(calendars_static STATIC
    ${CALENDARS_HEADERS}
    ${CALENDARS_SOURCES}
)

# libcalendars_STATIC is PUBLIC so that it applies both while compiling the
# archive itself and to everything that links against it. Were it INTERFACE the
# archive would be built with the dllexport attributes of a shared library.
target_compile_definitions(calendars_static PUBLIC libcalendars_STATIC)

# Ship the static library as libcalendars.a rather than libcalendars_static.a,
# so that -lcalendars resolves to it and the name matches what the pkg-config
# file advertises. MSVC is excluded because there the import library of the
# shared build already claims calendars.lib.
if(NOT MSVC)
    set_target_properties(calendars_static PROPERTIES OUTPUT_NAME calendars)
endif()

# Prepare the targets
set_target_properties(calendars calendars_static PROPERTIES
    VERSION 1.1.0
    SOVERSION 1
    C_STANDARD 90
    DEBUG_POSTFIX "_d"
    C_VISIBILITY_PRESET hidden
)

# DEFINE_SYMBOL is honoured for the shared library only, and is what selects the
# dllexport branch of cl-export.h while the library itself is being compiled.
set_target_properties(calendars PROPERTIES
    DEFINE_SYMBOL libcalendars_EXPORTS
)

foreach(target IN ITEMS calendars calendars_static)
    target_include_directories(${target}
        PUBLIC
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )

    if(UNIX)
        target_link_libraries(${target} PUBLIC m)
    endif()
endforeach()

# Installation

export(TARGETS calendars FILE "libcalendarsTargets.cmake")

install(TARGETS calendars calendars_static
    EXPORT "calendarsTargets"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# The pkg-config file is not installed on Windows. It carries the absolute
# prefix the build was configured with, which is wrong for a zip file that is
# unpacked anywhere, and the CMake package config below serves consumers there.
if(NOT WIN32)
    configure_file(
        "libcalendars.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/libcalendars.pc"
        @ONLY
    )

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libcalendars.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
    )
endif()

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "libcalendarsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT "calendarsTargets"
    FILE "libcalendarsTargets.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/libcalendars"
)

install(FILES
    "cmake/libcalendarsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libcalendarsConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/libcalendars"
)
