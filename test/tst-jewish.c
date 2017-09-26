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

#include "../src/cl-jewish.h"
#include "tst-common.h"
#include <stdio.h>

int main() {
    cal_to_jdn = &jw_to_jdn;
    jdn_to_cal = &jdn_to_jw;
    cal_to_gr = &jw_to_gr;
    gr_to_cal = &gr_to_jw;

    /* Specific day tests */
    int32_t jdn = 0;
    int16_t y;
    uint8_t m;
    uint16_t d;
    jw_to_jdn(&jdn, 4682, 3, 18);
    jdn_to_jw(jdn, &y, &m, &d);
    return tst_calendar(0, 2488069);
}
