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

#include <math.h>
#include <stdlib.h>
#include "cl-gregorian.h"
#include "cl-math.h"

LIBCALENDAR_API
uint8_t gr_is_leap(int16_t year) {
    if((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0)) {
        return 1;
    } else {
        return 0;
    }
}

LIBCALENDAR_API
uint8_t gr_days_in_month(uint8_t month, int16_t year) {
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;
        case 02:
            return gr_is_leap(year) ? 29 : 28;
            break;
        default:
            return 0;
            break;
    }
}

LIBCALENDAR_API
uint16_t gr_days_in_year(int16_t year) {
    return gr_is_leap(year) ? 366 : 365;
}

LIBCALENDAR_API
uint8_t gr_month_in_year(int16_t year) {
    return 12;
}

LIBCALENDAR_API
uint8_t gr_is_valid(int16_t year, uint8_t month, uint16_t day) {
    if(month <= gr_month_in_year(year) && day <= gr_days_in_month(month, year)) {
        return 1;
    }
    return 0;
}

LIBCALENDAR_API
void gr_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    const int8_t c0 = fdiv((month - 3) , 12);
    const int16_t x1 = month - (12 * c0) - 3;
    const int16_t x4 = year + c0;
    const div_t d = pdiv(x4, 100);
    *jd = fdiv(146097 * d.quot,  4)
          + fdiv(36525 * d.rem, 100)
          + fdiv(153 * x1 + 2 , 5)
          + day + 1721119;
}

LIBCALENDAR_API
void jdn_to_gr(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    const div_t x3 = pdiv(4 * jd - 6884477, 146097);
    const div_t x2 = pdiv(100 * (x3.rem / 4) + 99, 36525);
    const div_t x1 = pdiv(5 * (x2.rem / 100) + 2, 153);
    const uint16_t c0 = (x1.quot + 2) / 12;
    *day = (x1.rem / 5) + 1;
    *month = x1.quot - 12 * c0 + 3;
    *year = 100 * x3.quot + x2.quot + c0;
}
