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

#include <stdint.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "../src/cl-gregorian.h"

int tst_calendar(
    void (*cal_to_jdn)(uint32_t*, int16_t, uint8_t, uint16_t),
    void (*jdn_to_cal)(uint32_t, int16_t*, uint8_t*, uint16_t*),
    void (*cal_to_gr)(int16_t , uint8_t , uint16_t , int16_t*, uint8_t*, uint16_t*),
    void (*gr_to_cal)(int16_t , uint8_t , uint16_t , int16_t*, uint8_t*, uint16_t*),
    uint32_t min_jd, uint32_t max_jd);