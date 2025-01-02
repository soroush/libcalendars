# Copyright (C) 2021-2025 - Soroush Rabiei, <soroush.rabiei@gmail.com>
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

cmake_minimum_required(VERSION 3.16.0)

# Intermediate Object Library
add_library(calendars_object OBJECT 
    # Headers
    "include/libcalendars/cl-calendars.h"
    "include/libcalendars/cl-export.h"
    "include/libcalendars/cl-gregorian.h"
    "include/libcalendars/cl-islamic-civil.h"
    "include/libcalendars/cl-jewish.h"
    "include/libcalendars/cl-julian.h"
    "include/libcalendars/cl-milankovic.h"
    "include/libcalendars/cl-solar-hijri.h"
    "include/libcalendars/cl-egyptian.h"
    # Sources
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
)

if(WIN32)
    set(PLATFORM_SOURCES win32/libcalendars.rc)
else()
    set(PLATFORM_SOURCES "")
endif()

target_include_directories(calendars_object
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(calendars_object PROPERTIES
    C_STANDARD 90
    DEBUG_POSTFIX "_d"
    COMPILE_DEFINITIONS libcalendars_EXPORTS
)

# Define the shared library
add_library(calendars SHARED "${PLATFORM_SOURCES}" $<TARGET_OBJECTS:calendars_object>)

# Mark all public headers
file(GLOB_RECURSE ALL_HEADER_FILES "include/libcalendars/*.h")

# Prepate the target
set_target_properties(calendars PROPERTIES
    VERSION 1.1.0
    SOVERSION 0
    C_STANDARD 90
    DEBUG_POSTFIX "_d"
    DEFINE_SYMBOL libcalendars_EXPORTS
)

target_include_directories(calendars
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(UNIX)
target_link_libraries(calendars PUBLIC m)
endif()

# Define the static libray
add_library(calendars_static STATIC $<TARGET_OBJECTS:calendars_object>)

# Prepate the target
set_target_properties(calendars_static PROPERTIES
    VERSION 1.1.0
    SOVERSION 0
    C_STANDARD 90
    DEBUG_POSTFIX "_d"
)

target_compile_definitions(calendars_static INTERFACE libcalendars_STATIC)

target_include_directories(calendars_static
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(UNIX)
target_link_libraries(calendars PUBLIC m)
endif()

# Generate package config file

include(CMakePackageConfigHelpers)

# Installation

include(GNUInstallDirs)

export(TARGETS calendars FILE "libcalendarsTargets.cmake")

install(TARGETS calendars calendars_static
    EXPORT "calendarsTargets"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    # PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libcalendars"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "libcalendarsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT "calendarsTargets"
    FILE "libcalendarsTargets.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

install(FILES
    "cmake/libcalendarsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libcalendarsConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/"
)
