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

include_directories(PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/>)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Commont test mathematics
add_library(calendar_test_common OBJECT calendar-arithmetic.c)
target_link_libraries(calendar_test_common PUBLIC calendars)

link_libraries(calendar_test_common calendars)

add_executable(gregorian gregorian/gregorian.c)
add_executable(milankovic milankovic/milankovic.c)
add_executable(julian julian/julian.c)
add_executable(jewish jewish/jewish.c)
add_executable(islamic_civil islamic-civil/islamic-civil.c)
add_executable(solar_hijri solar-hijri/solar-hijri.c)
add_executable(egyptian egyptian/egyptian.c)
add_executable(babylonian babylonian/babylonian.c)

# The official Iranian calendar is set by observation and by decisions of the
# parliament, so it cannot be reproduced by the arithmetic rule alone. These
# two tests measure the disagreement against the published table.
set(SOLAR_HIJRI_GROUND_TRUTH_CSV
    "${CMAKE_CURRENT_SOURCE_DIR}/solar-hijri/official-leap-years.csv")

add_executable(solar_hijri_leap
    solar-hijri/solar-hijri-leap.c
    solar-hijri/ground-truth.c)
add_executable(solar_hijri_conversion
    solar-hijri/solar-hijri-conversion.c
    solar-hijri/ground-truth.c)

# Not a pass or fail test. It reports how the disagreement responds as leap
# years are pinned to the official table one at a time.
add_executable(solar_hijri_correction_sweep
    solar-hijri/solar-hijri-correction-sweep.c
    solar-hijri/ground-truth.c)

set_target_properties(
    gregorian julian milankovic solar_hijri solar_hijri_leap
    solar_hijri_conversion solar_hijri_correction_sweep jewish islamic_civil
    egyptian babylonian
    PROPERTIES
        C_STANDARD 90
        DEBUG_POSTFIX "_d"
)

# Add tests

add_test(NAME "Gregorian" COMMAND gregorian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Julian" COMMAND julian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Milankovic" COMMAND milankovic WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "SolarHijri" COMMAND solar_hijri WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "SolarHijriLeapGroundTruth"
    COMMAND solar_hijri_leap "${SOLAR_HIJRI_GROUND_TRUTH_CSV}"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "SolarHijriConversionGroundTruth"
    COMMAND solar_hijri_conversion "${SOLAR_HIJRI_GROUND_TRUTH_CSV}"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "SolarHijriCorrectionSweep"
    COMMAND solar_hijri_correction_sweep "${SOLAR_HIJRI_GROUND_TRUTH_CSV}"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Jewish" COMMAND jewish WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "IslamicCivil" COMMAND islamic_civil WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Egyptian" COMMAND egyptian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Babylonian" COMMAND babylonian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

if(WIN32)
set_tests_properties(Gregorian Julian Milankovic SolarHijri SolarHijriLeapGroundTruth SolarHijriConversionGroundTruth SolarHijriCorrectionSweep Jewish IslamicCivil Egyptian Babylonian PROPERTIES
    ENVIRONMENT "PATH=$<TARGET_FILE_DIR:calendars>;$ENV{PATH}"
)
else()
set_tests_properties(Gregorian Julian Milankovic SolarHijri SolarHijriLeapGroundTruth SolarHijriConversionGroundTruth SolarHijriCorrectionSweep Jewish IslamicCivil Egyptian Babylonian PROPERTIES
    ENVIRONMENT "LD_LIBRARY_PATH=$<TARGET_FILE_DIR:calendars>:$ENV{LD_LIBRARY_PATH}"
)
endif()