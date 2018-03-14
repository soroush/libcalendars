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

#ifndef LIBCALENDAR_CALENDARS_H
#define LIBCALENDAR_CALENDARS_H

#include <stdint.h>
#include "cl-export.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CAL_GREGORIAN       0x01    /* 0b00000001 */
#define CAL_JULIAN          0x02    /* 0b00000010 */
#define CAL_MILANKOVIC      0x04    /* 0b00000100 */
#define CAL_REVISED_JULIAN  CAL_MILANKOVIC
#define CAL_ISLAMIC_CIVIL   0x08    /* 0b00001000 */
#define CAL_HIJRI           CAL_ISLAMIC_CIVIL
#define CAL_JEWSISH         0x10    /* 0b00010000 */
#define CAL_HEBREW          CAL_JEWSISH
#define CAL_SOLAR_HIJRI     0x20    /* 0b00100000 */
#define CAL_SHAMSI          CAL_SOLAR_HIJRI
#define CAL_PERSIAN         CAL_SOLAR_HIJRI

/**
 * Decide wheter a given year number in a specified calendar is a leap year
 * (have some extra number of month or days) or not.
 */
LIBCALENDAR_API uint8_t  is_leap(uint8_t calendar, int16_t year);

/**
 * Returns number of days in a given year for specified calendar type.
 */
LIBCALENDAR_API uint8_t  days_in_month(uint8_t calendar, uint8_t month, int16_t year);

/**
 * Returns number of days of a specific month in a given year for specified
 * calendar type.
 */
LIBCALENDAR_API uint16_t days_in_year(uint8_t calendar, int16_t year);


/**
 * Returns number of month in a given year for specified calendar type.
 */
LIBCALENDAR_API uint8_t  month_in_year(uint8_t calendar, int16_t year);


/**
 * Checks if a givend date is valid is specified calendar or not (exists, or
 * fits in calendar rules).
 */
LIBCALENDAR_API uint8_t  is_valid(uint8_t calendar,
                                  int16_t year, uint8_t month, uint16_t day);

/**
 * Converts a given date (year, month, day) to Julian Day Number.
 */
LIBCALENDAR_API void to_jdn(uint8_t calendar, uint32_t* jd,
                            int16_t year, uint8_t month, uint16_t day);

/**
 * Converts a Julian Day Number to date (year, month, day).
 */
LIBCALENDAR_API void to_date(uint8_t calendar, uint32_t jd,
                             int16_t* year, uint8_t* month, uint16_t* day);

/**
 * Converts a date in a calendar to corresponding date in another calendar.
 */
LIBCALENDAR_API void convert_date(uint8_t icalendar, uint8_t ocalendar,
                                  int16_t iyear, uint8_t imonth, uint16_t iday,
                                  int16_t* oyear, uint8_t* omonth, uint16_t* oday);

#ifdef __cplusplus
}
#endif

#endif /* LIBCALENDAR_CALENDARS_H */
