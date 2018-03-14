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

#ifndef LIBCALENDAR_JULIAN_H
#define LIBCALENDAR_JULIAN_H

#include <stdint.h>
#include "cl-export.h"

#ifdef __cplusplus
extern "C" {
#endif

LIBCALENDAR_API uint8_t  ju_is_leap(int16_t year);
LIBCALENDAR_API uint8_t  ju_days_in_month(uint8_t month, int16_t year);
LIBCALENDAR_API uint16_t ju_days_in_year(int16_t year);
LIBCALENDAR_API uint8_t  ju_month_in_year(int16_t year);
LIBCALENDAR_API uint8_t  ju_is_valid(int16_t year, uint8_t month, uint16_t day);
LIBCALENDAR_API void ju_to_jdn(uint32_t* jd,
                               int16_t year, uint8_t month, uint16_t day);
LIBCALENDAR_API void jdn_to_ju(uint32_t jdn,
                               int16_t* year, uint8_t* month, uint16_t* day);
LIBCALENDAR_API void ju_to_gr(int16_t  jyear, uint8_t  jmonth, uint16_t  jday,
                              int16_t* gyear, uint8_t* gmonth, uint16_t* gday);
LIBCALENDAR_API void gr_to_ju(int16_t  gyear, uint8_t  gmonth, uint16_t  gday,
                              int16_t* jyear, uint8_t* jmonth, uint16_t* jday);

#ifdef __cplusplus
}
#endif

#endif /* LIBCALENDAR_GREGORIAN_H */
