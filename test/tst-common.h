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

#ifndef LIBCALENDAR_TST_COMMON_H
#define LIBCALENDAR_TST_COMMON_H

#include <stdint.h>
#include <stdio.h>

uint32_t min_jd = 0;
uint32_t max_jd = 2488069;

void (*cal_to_jdn)(uint32_t*, int16_t, uint8_t, uint16_t);
void (*jdn_to_cal)(uint32_t, int16_t*, uint8_t*, uint16_t*);

int tst_calendar() {
    uint32_t jdn = 0;
    uint32_t jdn2 = 0;
    for(jdn = min_jd; jdn < max_jd; ++jdn) {
        int16_t year;
        uint8_t month;
        uint16_t day;
        (*jdn_to_cal)(jdn, &year, &month, &day);
        (*cal_to_jdn)(&jdn2, year, month, day);
        if(jdn != jdn2) {
            printf("conversion failed! %d != %d for %+04d-%02d-%02d\n",
                   jdn, jdn2, year, month, day);
            return -1;
        }
    }
    return 0;
}

#endif /* LIBCALENDAR_TST_COMMON_H */
