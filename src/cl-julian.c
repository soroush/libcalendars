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
#include "cl-julian.h"
#include "cl-gregorian.h"
#include "cl-math.h"

LIBCALENDAR_API
uint8_t ju_is_leap(int16_t year) {
    if(year < 0) {
        ++year;
    }
    return mod(year, 4) == 0 ? 1 : 0;
}

LIBCALENDAR_API
uint8_t ju_days_in_month(uint8_t month, int16_t year) {
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
            return ju_is_leap(year) ? 29 : 28;
            break;
        default:
            return 0;
            break;
    }
}

LIBCALENDAR_API
uint16_t ju_days_in_year(int16_t year) {
    return ju_is_leap(year) ? 366 : 365;
}

LIBCALENDAR_API
uint8_t ju_month_in_year(int16_t year) {
    return 12;
}

LIBCALENDAR_API
uint8_t ju_is_valid(int16_t year, uint8_t month, uint16_t day) {
    if(day > 0 && day <= ju_days_in_month(month, year)) {
        return 1;
    }
    return 0;
}

LIBCALENDAR_API
void ju_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    int32_t c0 = 0;
    int32_t j1 = 0;
    int32_t j2 = 0;
    if(!year) {
        *jd = 0;
    }
    if(year < 0) {
        ++year;
    }
    c0 = fdiv(month - 3, 12);
    j1 = fdiv(1461 * (year + c0), 4);
    j2 = fdiv(153 * month - 1836 * c0 - 457, 5);
    *jd = j1 + j2 + day + 1721117;
}

LIBCALENDAR_API
void jdn_to_ju(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    const int32_t y2 = jd - 1721118;
    const int32_t k2 = 4 * y2 + 3;
    const int32_t k1 = 5 * fdiv(mod(k2, 1461), 4) + 2;
    const int32_t x1 = fdiv(k1, 153);
    const int32_t c0 = fdiv(x1 + 2, 12);
    *year = (int16_t)(fdiv(k2, 1461) + c0);
    if(*year <= 0) {
        --(*year);
    }
    *month = (uint8_t)(x1 - 12 * c0 + 3);
    *day = fdiv(mod(k1, 153), 5) + 1;
}

LIBCALENDAR_API
void ju_to_gr(int16_t  jyear,  uint8_t jmonth,  uint16_t jday,
              int16_t* gyear, uint8_t* gmonth, uint16_t* gday) {
    uint32_t jdn = 0;
    ju_to_jdn(&jdn, jyear, jmonth, jday);
    jdn_to_gr(jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void gr_to_ju(int16_t  gyear,  uint8_t gmonth,  uint16_t gday,
              int16_t* jyear, uint8_t* jmonth, uint16_t* jday) {
    uint32_t jdn = 0;
    gr_to_jdn(&jdn, gyear, gmonth, gday);
    jdn_to_ju(jdn, jyear, jmonth, jday);
}
