/*
* Copyright 2021 - Soroush Rabiei, <soroush.rabiei@gmail.com>
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

#ifndef LIBCALENDARS_EXPORT_H
#define LIBCALENDARS_EXPORT_H

#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
  #ifdef libcalendars_EXPORTS
    #ifdef __GNUC__
      #define LIBCALENDAR_API __attribute__ ((dllexport))
    #else
      #define LIBCALENDAR_API __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define LIBCALENDAR_API __attribute__ ((dllimport))
    #else
      #define LIBCALENDAR_API __declspec(dllimport)
    #endif
  #endif
  #define LIBCALENDAR_PRIVATE
#else
  #if __GNUC__ >= 4
    #define LIBCALENDAR_API __attribute__ ((visibility ("default")))
    #define LIBCALENDAR_PRIVATE  __attribute__ ((visibility ("hidden")))
  #else
    #define LIBCALENDAR_API
    #define LIBCALENDAR_PRIVATE
  #endif
#endif

#endif /* LIBCALENDARS_EXPORT_H */