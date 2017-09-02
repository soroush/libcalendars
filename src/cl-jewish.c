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
#include "cl-jewish.h"
#include "cl-gregorian.h"
#include "cl-math.h"

LIBCALENDAR_API
int jw_is_leap(int16_t year)
{
}

LIBCALENDAR_API
int jw_days_in_month(uint8_t month, int16_t year)
{
}

LIBCALENDAR_API
uint16_t jw_days_in_year(int16_t year)
{
}

static int32_t c1(int32_t x)
{
    return clm_floor_div(235 * x + 1, 19);
}

static int32_t q(int32_t x)
{
    return clm_floor_div(c1(x), 1095);
}

static int32_t r(int32_t x)
{
    return clm_mod(c1(x), 1095);
}

static int32_t v1(int32_t x)
{
    return 32336 * q(x)
           + clm_floor_div(15 * q(x) + 765433 * r(x) + 12084, 25920);
}

static int32_t v2(int32_t x)
{
    return v1(x) + clm_mod(clm_floor_div(clm_mod(6 * v1(x), 7), 7), 2);
}

static int32_t L(int32_t x)
{
    return v2(x + 1) - v2(x);
}

static int32_t v3(int32_t x1)
{
    return 2 * clm_mod(clm_floor_div(L(x1) + 19, 15), 2);
}

static int32_t v4(int32_t x1)
{
    return clm_mod(clm_floor_div(L(x1 - 1) + 7, 15), 2);
}

LIBCALENDAR_API
void jw_to_jdn(uint32_t *jd, int16_t year, uint8_t month, uint16_t day)
{
    const int32_t c0 = clm_floor_div(13 - month, 7);
    const int32_t x1 = year - 1 + c0;
    const int32_t x3 = month - 1;
    const int32_t z4 = day - 1;
    const int32_t L2_x1_0 = v2(x1 + 1) - v2(x1);
    const int32_t L2_x1_1 = v2(x1) - v2(x1 - 1);
}

LIBCALENDAR_API
void jdn_to_jw(uint32_t jd, int16_t *year, uint8_t *month, uint16_t *day)
{
}

LIBCALENDAR_API
void jw_to_gr(int16_t  jyear,  uint8_t jmonth,  uint16_t jday,
              int16_t *gyear, uint8_t *gmonth, uint16_t *gday)
{
}

LIBCALENDAR_API
void gr_to_jw(int16_t  gyear,  uint8_t gmonth,  uint16_t gday,
              int16_t *jyear, uint8_t *jmonth, uint16_t *jday)
{
}
