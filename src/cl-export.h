/*
* Copyright 2017 - Soroush Rabiei, <soroush@ametisco.ir>
* This file is part of libcalendars.
*
* libcalendars is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* libcalendars is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef LIBCALENDAR_EXPORT_H
#define LIBCALENDAR_EXPORT_H

#if defined(LIBCALENDAR_EXPORT)
    #if defined(_MSC_VER)
        #define LIBCALENDAR_API __declspec(dllexport)
    #else
        #define LIBCALENDAR_API __attribute__((visibility("default")))
    #endif
#elif defined(LIBCALENDAR_STATIC)
    #define LIBCALENDAR_API
#else
#if defined(_MSC_VER)
        #define LIBCALENDAR_API __declspec(dllimport)
#else
        #define LIBCALENDAR_API
#endif

#endif

#endif
