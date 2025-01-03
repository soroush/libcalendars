/*
 * Copyright (C) 2021-2025 - Soroush Rabiei, <soroush.rabiei@gmail.com>
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

#include <stdint.h>
#include <stdio.h>
#include <libcalendars/cl-gregorian.h>
#include "calendar-arithmetic.h"

void test_julian_day(
    test_context* ctx,
    uint32_t in_jd, uint32_t* out_jd)
{
    int16_t year;
    uint8_t month;
    uint16_t day;
    ctx->jdn_to_cal(in_jd, &year, &month, &day);
    ctx->cal_to_jdn(out_jd, year, month, day);
}

void test_gregorian_calendar(
    test_context* ctx,
    uint32_t in_jd, int16_t* gyi, uint8_t* gmi, uint16_t* gdi, int16_t* gyo, uint8_t* gmo, uint16_t* gdo)
{
    int16_t year;
    uint8_t month;
    uint16_t day;
    jdn_to_gr(in_jd, gyi, gmi, gdi);
    ctx->gr_to_cal(*gyi, *gmi, *gdi, &year, &month, &day);
    ctx->cal_to_gr(year, month, day, gyo, gmo, gdo);
}

// void test_continuity(test_context ctx,  uint8_t* valid)
// {

// }