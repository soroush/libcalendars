cmake_minimum_required(VERSION 3.16.0)

project(calendars 
    VERSION 1.1.0 
    DESCRIPTION "A calendar arithmetic library"
    HOMEPAGE_URL "https://github.com/soroush/libcalendars"
    LANGUAGES C
)

enable_testing()

add_subdirectory(lib)
add_subdirectory(tests)