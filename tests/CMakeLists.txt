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

# Calendar tests

enable_language(CXX)
enable_testing()

link_libraries(calendars GTest::gtest GTest::gtest_main $<IF:$<TARGET_EXISTS:Check::check>,Check::check,Check::checkShared>)

include_directories(PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/>)

file(GLOB_RECURSE ALL_SOURCES "*.c")

set_property(SOURCE ${ALL_SOURCES} PROPERTY LANGUAGE CXX)

add_executable(tst_gregorian tst-common.c tst-common.h tst-gregorian.c)
add_executable(tst_milankovic tst-common.c tst-common.h tst-milankovic.c)
add_executable(tst_julian tst-common.c tst-common.h tst-julian.c)
add_executable(tst_jewish tst-common.c tst-common.h tst-jewish.c)
add_executable(tst_islamic_civil tst-common.c tst-common.h tst-islamic-civil.c)

# add_executable(tst_solar_hijri 
#     calendar-arithmetic.cpp
#     tst-solar-hijri.cpp
#     )
    
    add_executable(tst_solar_hijri
    tst-solar-hijri.c
    calendar-arithmetic.c
)

set_target_properties(tst_gregorian tst_julian tst_milankovic tst_solar_hijri tst_jewish tst_islamic_civil
    PROPERTIES
        C_STANDARD 90
        DEBUG_POSTFIX "_d"
)

# Add tests

add_test(NAME "Gregorian" COMMAND tst_gregorian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Julian" COMMAND tst_julian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Milankovic" COMMAND tst_milankovic WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "SolarHijri" COMMAND tst_solar_hijri WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
# add_test(NAME "SolarHijri_C" COMMAND tst_solar_hijri_c WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Jewish" COMMAND tst_jewish WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "IslamicCivil" COMMAND tst_islamic_civil WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_custom_command(TARGET tst_gregorian tst_julian tst_milankovic tst_solar_hijri tst_jewish tst_islamic_civil
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:calendars>" "$<TARGET_FILE_DIR:tst_gregorian>"
    COMMENT "Copy dll file to $<TARGET_FILE_DIR:tst_gregorian> directory" VERBATIM
)