/*
 * Copyright (C) 2021-2025 - Soroush Rabiei, <soroush.rabiei@gmail.com>
 * This file is part of libcalendar.
 *
 * libcalendar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LIBCALENDARS_EXPORT_H
#define LIBCALENDARS_EXPORT_H

/*
 * LIBCALENDAR_API marks a symbol as part of the public interface, and must be
 * repeated on both the declaration and the definition of every such symbol.
 * LIBCALENDAR_PRIVATE marks an internal symbol that is shared between
 * translation units but must not leave the library.
 *
 * On Windows the distinction is carried by the import/export attributes, and
 * libcalendars_STATIC must be defined by anything linking the static library.
 * Elsewhere it is carried by ELF visibility, which applies to the static and
 * shared builds alike -- so libcalendars_STATIC is meaningless there.
 */

#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
  #define LIBCALENDAR_PRIVATE
  #if defined libcalendars_STATIC
    #define LIBCALENDAR_API
  #elif defined libcalendars_EXPORTS
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
#elif defined __GNUC__ && __GNUC__ >= 4
  #define LIBCALENDAR_API     __attribute__ ((visibility ("default")))
  #define LIBCALENDAR_PRIVATE __attribute__ ((visibility ("hidden")))
#else
  #define LIBCALENDAR_API
  #define LIBCALENDAR_PRIVATE
#endif

#endif /* LIBCALENDARS_EXPORT_H */
