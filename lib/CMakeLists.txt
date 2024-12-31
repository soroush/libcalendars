cmake_minimum_required(VERSION 3.16.0)

set(LIBCAL_SOURCES
    # Headers
    include/libcalendars/cl-calendars.h
    include/libcalendars/cl-export.h
    include/libcalendars/cl-gregorian.h
    include/libcalendars/cl-islamic-civil.h
    include/libcalendars/cl-jewish.h
    include/libcalendars/cl-julian.h
    include/libcalendars/cl-milankovic.h
    include/libcalendars/cl-solar-hijri.h
    # Sources
    src/cl-math.h
    src/cl-math.c
    src/cl-calendars.c
    src/cl-gregorian.c
    src/cl-julian.c
    src/cl-milankovic.c
    src/cl-solar-hijri.c
    src/cl-islamic-civil.c
    src/cl-jewish.c
)

if(WIN32)
    list(APPEND LIBCAL_SOURCES win32/libcalendars.rc)
endif()

# Define the library
add_library(calendars SHARED ${LIBCAL_SOURCES})

# Mark all public headers
file(GLOB_RECURSE ALL_HEADER_FILES "include/libcalendars/*.h")

# Prepate the target
set_target_properties(calendars PROPERTIES
    VERSION 1.1.0
    SOVERSION 0
    C_STANDARD 90
    DEBUG_POSTFIX "_d"
    PUBLIC_HEADER "${ALL_HEADER_FILES}"
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

# Testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# Generate package config file

include(CMakePackageConfigHelpers)

configure_package_config_file(libcalendars.pc.in libcalendars.pc
    INSTALL_DESTINATION ${LIB_INSTALL_DIR}/libcalendars
)

# Installation

include(GNUInstallDirs)

export(TARGETS calendars FILE "libcalendarsTargets.cmake")

install(TARGETS calendars
    EXPORT "calendarsTargets"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libcalendars"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libcalendars")

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

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/calendars.pc"
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig"
)
