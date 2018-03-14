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
#include <stddef.h>
#include "cl-solar-hijri.h"
#include "cl-gregorian.h"
#include "cl-math.h"

/* Constants */

/* Number of days in a cycle */
static const int32_t cycle_days = 1029983;
/* Number of years in a cycle */
static const uint16_t cycle_years = 2820;
/* 365 + leapRatio */
static const double year_length = 365.24219858156028368;
/* 475/01/01 AP, start of 2820 cycle */
static const uint32_t hijri_shamsi_epoch = 2121446;
/* 683.0 / 2820.0 */
static const double leap_threshold = 0.24219858156028368;

LIBCALENDAR_API
uint8_t sh_is_leap(int16_t year) {
    double integral;
    double frac;
    frac = modf((year + 2346) * leap_threshold, &integral);
    if(frac < leap_threshold) {
        return 1;
    } else {
        return 0;
    }
}

LIBCALENDAR_API
uint8_t sh_days_in_month(uint8_t month, int16_t year) {
    if(month > 0 && month <= 12) {
        return month < 7 ? 31 : month < 12 || sh_is_leap(year) ? 30 : 29;
    }

    return 0;
}

int16_t cycle(uint32_t jdn) {
    const int32_t offset = jdn - hijri_shamsi_epoch;
    int16_t cycle_no = offset / cycle_days;
    if(offset < 0) {
        --cycle_no;
    }
    return cycle_no;
}

LIBCALENDAR_API
uint16_t sh_days_in_year(int16_t year) {
    return sh_is_leap(year) ? 366 : 365;
}

LIBCALENDAR_API uint8_t sh_month_in_year(int16_t year) {
    return 12;
}

LIBCALENDAR_API uint8_t sh_is_valid(int16_t year, uint8_t month, uint16_t day) {
    if(year < 0)
        ++year;
    if(day > 0 && day <= sh_days_in_month(month, year)) {
        return 1;
    }
    return 0;
}

static uint32_t cycle_start(uint32_t jdn) {
    const int16_t era = cycle(jdn);
    const uint32_t start = hijri_shamsi_epoch + era * cycle_days;
    return start;
}

static uint32_t fdoy_c(int year, int cycleNo) {
    const double d_c = (year * year_length); /* Day in cycle */
    /* First day of year in a cycle */
    const uint32_t fdoy_c = (uint32_t)(floor(d_c));
    return hijri_shamsi_epoch + cycleNo * cycle_days + fdoy_c ;
}

static uint32_t fdoy(int year) {
    /* Cycle number */
    int16_t c = year / cycle_years;
    /* First day of year in a cycle */
    uint32_t fdoy_c;
    /* Day number in cycle */
    double d_c;
    year -= 475;
    if(year < 0) {
        c--;
    }
    year -= (c * cycle_years);
    d_c = (year * year_length);
    fdoy_c = (uint32_t)(floor(d_c));
    return hijri_shamsi_epoch + c * cycle_days + fdoy_c ;
}

LIBCALENDAR_API
void sh_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    /* Adjust the offset of year 0 */
    int16_t era = 0;
    int32_t d_y = 0;
    int32_t y_c = 0;
    int32_t f_d = 0;
    size_t i = 0;
    if(year < 0) {
        ++year;
    }
    era = (year - 475) / cycle_years;
    if((year - 475) < 0) {
        --era;
    }
    y_c = (year - 475) - era * cycle_years;
    f_d = fdoy_c(y_c, era);
    d_y = 0;
    for(i = 1; i < month; ++i) {
        d_y += sh_days_in_month(i, year);
    }
    d_y += day;
    *jd = f_d + d_y - 1;
}

LIBCALENDAR_API
void jdn_to_sh(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    const int c = cycle(jd);
    const int16_t y_c = (int16_t)(floor((jd - cycle_start(jd)) / year_length));
    int16_t y = y_c + 475 + c * 2820;
    uint16_t d = jd - fdoy_c(y_c, c) + 1;
    uint8_t m = 0;
    if(d > sh_days_in_year(y)) {
        y++;
        d = 1;
    }
    if(y <= 0) {
        y--;
    }
    for(m = 1; m < 12; ++m) {
        if(d > sh_days_in_month(m, y)) {
            d -= sh_days_in_month(m, y);
        } else {
            break;
        }
    }
    *year = y;
    *month = m;
    *day = d;
}

LIBCALENDAR_API
void sh_to_gr(int16_t  jyear,  uint8_t jmonth,  uint16_t jday,
              int16_t* gyear, uint8_t* gmonth, uint16_t* gday) {
    uint32_t jdn = 0;
    sh_to_jdn(&jdn, jyear, jmonth, jday);
    jdn_to_gr(jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void gr_to_sh(int16_t  gyear,  uint8_t gmonth,  uint16_t gday,
              int16_t* jyear, uint8_t* jmonth, uint16_t* jday) {
    uint32_t jdn = 0;
    gr_to_jdn(&jdn, gyear, gmonth, gday);
    jdn_to_sh(jdn, jyear, jmonth, jday);
}
