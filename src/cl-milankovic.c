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
#include "cl-milankovic.h"
#include "cl-gregorian.h"
#include "cl-math.h"

LIBCALENDAR_API
uint8_t ml_is_leap(int16_t year) {
    if(year <= 0) {
        ++year;
    }
    if(mod(year, 4) == 0) {
        if(mod(year, 100) == 0) {
            const int16_t century = mod(fdiv(year, 100), 9);
            if(century == 2 || century == 6) {
                return 1;
            } else {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

LIBCALENDAR_API
uint8_t ml_days_in_month(uint8_t month, int16_t year) {
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
            return ml_is_leap(year) ? 29 : 28;
            break;
        default:
            return 0;
            break;
    }
}

LIBCALENDAR_API
uint16_t ml_days_in_year(int16_t year) {
    return ml_is_leap(year) ? 366 : 365;
}

LIBCALENDAR_API uint8_t ml_month_in_year(int16_t year) {
    return 12;
}

LIBCALENDAR_API
uint8_t ml_is_valid(int16_t year, uint8_t month, uint16_t day) {

    if(day > 0 && day <= ml_days_in_month(month, year)) {
        return 1;
    }
    return 0;
}

LIBCALENDAR_API
void ml_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    int8_t c0;
    int16_t x1 = 0;
    int16_t x2 = 0;
    int16_t x3 = 0;
    int16_t x4 = 0;
    if(year <= 0) {
        ++year;
    }
    c0 = fdiv((month - 3) , 12);
    x1 = month - (12 * c0) - 3;
    x4 = year + c0;
    x3 = fdiv(x4, 100);
    x2 = mod(x4, 100);
    *jd = fdiv(328718 * x3 + 6, 9)
          + fdiv(36525 * x2 , 100)
          + fdiv(153 * x1 + 2 , 5)
          + day + 1721119;
}

LIBCALENDAR_API
void jdn_to_ml(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    const int32_t k3 = 9 * (jd - 1721120) + 2;
    const int32_t x3 = fdiv(k3, 328718);
    const int32_t k2 = 100 * fdiv(mod(k3, 328718), 9) + 99;
    const int32_t k1 = fdiv(mod(k2, 36525), 100) * 5 + 2;
    const int32_t x2 = fdiv(k2, 36525);
    const int32_t x1 =
        fdiv(5 * fdiv(mod(k2, 36525), 100) + 2, 153);
    const uint32_t c0 = fdiv(x1 + 2, 12);
    *year = (int16_t)(100 * x3 + x2 + c0);
    if(*year <= 0) {
        --(*year);
    }
    *month = (uint8_t)(x1 - 12 * c0 + 3);
    *day = fdiv(mod(k1, 153), 5) + 1;
}

LIBCALENDAR_API
void ml_to_gr(int16_t  jyear,  uint8_t jmonth,  uint16_t jday,
              int16_t* gyear, uint8_t* gmonth, uint16_t* gday) {
    uint32_t jdn = 0;
    ml_to_jdn(&jdn, jyear, jmonth, jday);
    jdn_to_gr(jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void gr_to_ml(int16_t  gyear,  uint8_t gmonth,  uint16_t gday,
              int16_t* jyear, uint8_t* jmonth, uint16_t* jday) {
    uint32_t jdn = 0;
    gr_to_jdn(&jdn, gyear, gmonth, gday);
    jdn_to_ml(jdn, jyear, jmonth, jday);
}

