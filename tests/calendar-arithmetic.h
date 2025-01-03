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

#pragma once

#include <stdint.h>
#include <stdio.h>

typedef struct _test_context
{
    void (*cal_to_jdn)(uint32_t*, int16_t, uint8_t, uint16_t);
    void (*jdn_to_cal)(uint32_t, int16_t*, uint8_t*, uint16_t*);
    void (*cal_to_gr)(int16_t, uint8_t, uint16_t, int16_t*, uint8_t*, uint16_t*);
    void (*gr_to_cal)(int16_t, uint8_t, uint16_t, int16_t*, uint8_t*, uint16_t*);
    uint32_t min_jd;
    uint32_t max_jd;
} test_context;

void test_julian_day(
    // void (*cal_to_jdn)(uint32_t*, int16_t, uint8_t, uint16_t),
    // void (*jdn_to_cal)(uint32_t, int16_t*, uint8_t*, uint16_t*),
    test_context* ctx,
    uint32_t in_jd, uint32_t* out_jd);

void test_gregorian_calendar(
    // void (*cal_to_gr)(int16_t, uint8_t, uint16_t, int16_t*, uint8_t*, uint16_t*),
    // void (*gr_to_cal)(int16_t, uint8_t, uint16_t, int16_t*, uint8_t*, uint16_t*),
    test_context* ctx,
    uint32_t in_jd, int16_t*, uint8_t*, uint16_t*, int16_t*, uint8_t*, uint16_t*);

void test_continuity(test_context ctx, uint32_t jdn, uint8_t* valid);