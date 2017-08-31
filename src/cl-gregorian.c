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
#include "cl-gregorian.h"
#include "cl-math.h"

LIBCALENDAR_API
int gr_is_leap(int16_t year) {
    if((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0)) {
        return 1;
    } else {
        return 0;
    }
}

LIBCALENDAR_API
int gr_days_in_month(uint8_t month, int16_t year) {
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
            return gr_is_leap(year) ? 29 : 28;
            break;
        default:
            return 0;
            break;
    }
}

LIBCALENDAR_API
uint16_t gr_days_in_year(int16_t year) {
    return gr_is_leap(year) ? 366 : 365;
}


LIBCALENDAR_API
void gr_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    int8_t c0;
    int16_t x4;
    int16_t x1;
    div_t d;
    c0 = clm_floor_div((month - 3) , 12);
    x1 = month - (12 * c0) - 3;
    x4 = year + c0;
    d = clm_pdiv(x4, 100);
    *jd = clm_floor_div(146097 * d.quot,  4)
          + clm_floor_div(36525 * d.rem, 100)
          + clm_floor_div(153 * x1 + 2 , 5)
          + day + 1721119;
}

LIBCALENDAR_API
void jdn_to_gr(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    div_t x3_r3 = clm_pdiv(4 * jd - 6884477, 146097);
    div_t x2_r2 = clm_pdiv(100 * (x3_r3.rem / 4) + 99, 36525);
    div_t x1_r1 = clm_pdiv(5 * (x2_r2.rem / 100) + 2, 153);
    uint16_t c0 = (x1_r1.quot + 2) / 12;
    *day = (x1_r1.rem / 5) + 1;
    *month = x1_r1.quot - 12*c0 + 3;
    *year = 100 * x3_r3.quot + x2_r2.quot + c0;
}
