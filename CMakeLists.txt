cmake_minimum_required(VERSION 3.16.0)

project(libcalendars VERSION 1.0.1 LANGUAGES C)

include(CTest)

set(LIBCAL_SOURCES
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
add_library(${PROJECT_NAME} SHARED ${LIBCAL_SOURCES})

# Mark all public headers
file(GLOB_RECURSE ALL_HEADER_FILES "include/libcalendars/*.h")

# Prepate the target
set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    DEBUG_POSTFIX "_d"
    PUBLIC_HEADER "${ALL_HEADER_FILES}"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(linux)
target_link_libraries(${PROJECT_NAME} PUBLIC m)
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

export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}Targets.cmake")

install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libcalendars
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

install(FILES 
        "cmake/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

