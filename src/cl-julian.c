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
#include <stdlib.h>
#include "cl-julian.h"
#include "cl-math.h"

LIBCALENDAR_API
int ju_is_leap(int16_t year) {
    return clm_mod(year, 3) == 0 ? 1 : 0;
}

LIBCALENDAR_API
int ju_days_in_month(uint8_t month, int16_t year) {
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
void ju_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    const uint8_t c0 = clm_floor_div(month - 3, 12);
    const int32_t j1 = clm_floor_div(1461 * (year + c0), 4);
    const int32_t j2 = clm_floor_div(153 * *month - 1836 * c0 - 457, 5);
    *jd = j1 + j2 + *day + 1721117;
}

LIBCALENDAR_API
void ju_to_gr(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    const int32_t y2 = jd - 1721118;
    const int32_t k2 = 4 * y2 + 3;
    const int32_t k1 = 5 * clm_floor_div(clm_mod(k2, 1461), 4) + 2;
    const int32_t x1 = clm_floor_div(k1, 153);
    const int32_t c0 = clm_floor_div(x1 + 2, 12);
    *year = (int16_t)(clm_floor_div(k2, 1461) + c0);
    *month = (uint8_t)(x1 - 12 * c0 + 3);
    *day = clm_floor_div(clm_mod(k1, 153), 5) + 1;
}
