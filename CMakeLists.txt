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
#

cmake_minimum_required(VERSION 3.16.0)

project(calendars 
    VERSION 1.1.0 
    DESCRIPTION "A calendar arithmetic library"
    HOMEPAGE_URL "https://github.com/soroush/libcalendars"
    LANGUAGES C
)

find_package(check CONFIG REQUIRED)

add_subdirectory(lib)

if(${check_FOUND})
    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "check library not found. Disabling the tests.")
endif()