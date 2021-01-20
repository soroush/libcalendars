cmake_minimum_required(VERSION 3.16.0)

project(libcalendars_tests VERSION 0.1.0 LANGUAGES C)

# Calendar tests

link_libraries(libcalendars)

include_directories(PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/>)

add_executable(tst_gregorian tst-common.c tst-common.h tst-gregorian.c)
add_executable(tst_milankovic tst-common.c tst-common.h tst-milankovic.c)
add_executable(tst_julian tst-common.c tst-common.h tst-julian.c)
add_executable(tst_solar_hijri tst-common.c tst-common.h tst-solar-hijri.c)
add_executable(tst_jewish tst-common.c tst-common.h tst-jewish.c)
add_executable(tst_islamic_civil tst-common.c tst-common.h tst-islamic-civil.c)

set_target_properties(tst_gregorian tst_julian tst_milankovic tst_solar_hijri tst_jewish tst_islamic_civil
    PROPERTIES 
        C_STANDARD 11 
        DEBUG_POSTFIX "_d"
)

# Add tests

add_test(NAME "Gregorian" COMMAND tst_gregorian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Julian" COMMAND tst_julian WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Milankovic" COMMAND tst_milankovic WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "SolarHijri" COMMAND tst_solar_hijri WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "Jewish" COMMAND tst_jewish WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME "IslamicCivil" COMMAND tst_islamic_civil WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
