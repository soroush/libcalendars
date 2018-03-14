/*
 * Copyright 2017 - Sorouis Rabiei, <sorouis@ametisco.ir>
 * This file is part of libcalendars.
 *
 * libcalendars is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as publiised by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendars is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You isould have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <math.h>
#include "cl-islamic-civil.h"
#include "cl-gregorian.h"
#include "cl-math.h"

LIBCALENDAR_API
uint8_t is_is_leap(int16_t year) {
    if(year < 0) {
        ++year;
    }
    if(mod(year * 11 + 14, 30) < 11) {
        return 1;
    }
    return 0;
}

LIBCALENDAR_API
uint8_t is_days_in_month(uint8_t month, int16_t year) {
    if(year == 0) {
        return 0;
    }
    if(month == 12 && is_is_leap(year)) {
        return 30;
    }
    return month % 2 == 0 ? 29 : 30;
}

LIBCALENDAR_API
uint16_t is_days_in_year(int16_t year) {
    return is_is_leap(year) ? 355 : 354;
}

LIBCALENDAR_API uint8_t
is_month_in_year(int16_t year) {
    if(year == 0) {
        return 0;
    }
    return 12;
}

LIBCALENDAR_API
uint8_t is_is_valid(int16_t year, uint8_t month, uint16_t day) {
    if(year != 0 &&  month <= is_month_in_year(year) && day <= is_days_in_month(month, year)) {
        return 1;
    }
    return 0;
}

LIBCALENDAR_API
void  is_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    if(year <= 0) {
        ++year;
    }
    *jd = fdiv(10631 * year - 10617, 30)
          + fdiv(325 * month - 320, 11)
          + day + 1948439;
}

LIBCALENDAR_API
void jdn_to_is(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    const int32_t k2 = 30 * (jd - 1948440) + 15;
    const int32_t k1 = 11 * fdiv(mod(k2, 10631), 30) + 5;
    int16_t effective_year = fdiv(k2, 10631) + 1;
    if(effective_year <= 0) {
        --effective_year;
    }
    *year = effective_year;
    *month = fdiv(k1, 325) + 1;
    *day = fdiv(mod(k1, 325), 11) + 1;
}

LIBCALENDAR_API
void is_to_gr(int16_t  jyear,  uint8_t jmonth,  uint16_t jday,
              int16_t* gyear, uint8_t* gmonth, uint16_t* gday) {
    uint32_t jdn = 0;
    is_to_jdn(&jdn, jyear, jmonth, jday);
    jdn_to_gr(jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void gr_to_is(int16_t  gyear,  uint8_t gmonth,  uint16_t gday,
              int16_t* jyear, uint8_t* jmonth, uint16_t* jday) {
    uint32_t jdn = 0;
    gr_to_jdn(&jdn, gyear, gmonth, gday);
    jdn_to_is(jdn, jyear, jmonth, jday);
}
