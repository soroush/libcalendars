/*
 * Copyright 2017 - Soroush Rabiei, <soroush@ametisco.ir>
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

#ifndef LIBCALENDAR_MILANKOVIC_H
#define LIBCALENDAR_MILANKOVIC_H

#include <stdint.h>
#include "cl-export.h"

#ifdef __cplusplus
extern "C" {
#endif

LIBCALENDAR_API int ml_is_leap(int16_t year);
LIBCALENDAR_API int ml_days_in_month(uint8_t month, int16_t year);
LIBCALENDAR_API uint16_t ml_days_in_year(int16_t year);
LIBCALENDAR_API void ml_to_jdn(uint32_t* jd,
                               int16_t year, uint8_t month, uint16_t day);
LIBCALENDAR_API void jdn_to_ml(uint32_t jdn,
                               int16_t* year, uint8_t* month, uint16_t* day);

#ifdef __cplusplus
}
#endif

#endif /* LIBCALENDAR_MILANKOVIC_H */
