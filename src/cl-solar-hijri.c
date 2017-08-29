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

#include <math.h>
#include "cl-solar-hijri.h"

/* Constants */

/* Number of days in a cycle */
static const int32_t cycle_days = 1029983;
/* Number of years in a cycle */
static const uint32_t cycle_years = 2820;
/* 365 + leapRatio */
static const double year_length = 365.24219858156028368;
/* 475/01/01 AP, start of 2820 cycle */
static const uint32_t hijri_shamsi_epoch = 2121446;
/* 683.0 / 2820.0 */
static const double leap_threshold = 0.24219858156028368;

LIBCALENDAR_API
int sh_is_leap(int16_t year)
{
    double integral;
    double frac;
    frac = modf((year + 2346) * leap_threshold, &integral);
    if(frac < leap_threshold)
        return 1;
    else
        return 0;
}

LIBCALENDAR_API
int sh_days_in_month(uint8_t month, int16_t year)
{
    if(month > 0 && month <= 12)
        return month < 7 ? 31 : month < 12 || sh_is_leap(year) ? 30 : 29;

    return 0;
}

int16_t cycle(uint32_t jdn)
{
    int32_t offset;
    int16_t cycle_no;
    offset = jdn - hijri_shamsi_epoch;
    cycle_no = offset / cycle_days;
    if(offset < 0)
        cycle_no--;
    return cycle_no;
}

LIBCALENDAR_API
uint16_t sh_days_in_year(int16_t year)
{
    return sh_is_leap(year) ? 366 : 365;
}

static uint32_t cycle_start(uint32_t jdn)
{
    int16_t e;
    uint32_t start;
    e = cycle(jdn);
    start = hijri_shamsi_epoch + e * cycle_days;
    return start;
}

static uint32_t fdoy_c(int year, int cycleNo)
{
    uint32_t fdoy_c;                         /* First day of year in a cycle */
    const double d_c = (year * year_length); /* Day in cycle */
    fdoy_c = (uint32_t)(floor(d_c));
    return hijri_shamsi_epoch + cycleNo * cycle_days + fdoy_c ;
}

static uint32_t fdoy(int year)
{
    int16_t c;        /* Cycle number */
    uint32_t fdoy_c;  /* First day of year in a cycle */
    double d_c;       /* Day number in cycle */
    year -= 475;
    c = year / cycle_years;
    if(year < 0)
        c--;
    year -= (c * cycle_years);
    d_c = (year * year_length);
    fdoy_c = (uint32_t)(floor(d_c));
    return hijri_shamsi_epoch + c * cycle_days + fdoy_c ;
}

LIBCALENDAR_API
void sh_to_jdn(uint32_t *jd, int16_t year, uint8_t month, uint16_t day)
{
    /* Adjust the offset of year 0 */
    int e = 0;
    int d_y = 0;
    int32_t f_d;
    if(year < 0)
        ++year;
    e = (year - 475) / cycle_years;
    if((year - 475) < 0)
        e--;
    int y_c = (year - 475) - e * cycle_years;
    f_d = fdoy_c(y_c, e);
    d_y = 0;
    for(int i = 1; i < month; ++i)
        d_y += sh_days_in_month(i, year);
    d_y += day;
    *jd = f_d + d_y - 1;
}

LIBCALENDAR_API
void jdn_to_sh(uint32_t jd, int16_t *year, uint8_t *month, uint16_t *day)
{
    const int c = cycle(jd);
    int16_t y_c = floor((jd - cycle_start(jd)) / year_length);
    int16_t y = y_c + 475 + c * 2820;
    uint32_t firstDay = fdoy_c(y_c, c);
    uint16_t d = jd - firstDay + 1;
    uint8_t m = 0;
    if(d > sh_days_in_year(y)) {
        y++;
        d = 1;
    }
    if(y <= 0)
        y--;
    for(m = 1; m < 12; ++m) {
        if(d > sh_days_in_month(m, y))
            d -= sh_days_in_month(m, y);
        else
            break;
    }
    *year = y;
    *month = m;
    *day = d;
}
