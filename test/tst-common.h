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
#include "../src/cl-gregorian.h"

uint32_t min_jd = 0;
uint32_t max_jd = 2488069;

void (*cal_to_jdn)(uint32_t*, int16_t, uint8_t, uint16_t);
void (*jdn_to_cal)(uint32_t, int16_t*, uint8_t*, uint16_t*);
void (*cal_to_gr)(int16_t  jyear, uint8_t  jmonth, uint16_t  jday,
                  int16_t* gyear, uint8_t* gmonth, uint16_t* gday);
void (*gr_to_cal)(int16_t  gyear, uint8_t  gmonth, uint16_t  gday,
                  int16_t* jyear, uint8_t* jmonth, uint16_t* jday);

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
            printf("JDN conversion failed! %d != %d for %+04d-%02d-%02d\n",
                   jdn, jdn2, year, month, day);
            return -1;
        }
        int16_t gy[2] = {0, 0};
        uint8_t gm[2] = {0, 0};
        uint16_t gd[2] = {0, 0};
        jdn_to_gr(jdn, &gy[0], &gm[0], &gd[0]);
        (*gr_to_cal)(gy[0], gm[0], gd[0], &year, &month, &day);
        (*cal_to_gr)(year, month, day, &gy[1], &gm[1], &gd[1]);
        if(gy[0] != gy[1] || gm[0] != gm[1] || gm[0] != gm[1]) {
            printf("Gregorian to calendar conversion failed! "
                   "%04d-%20d-%02d != %04d-%20d-%02d!\n",
                   gy[0], gm[0], gd[0], gy[1], gm[1], gd[1]);
            return -1;
        }

    }
    return 0;
}

#endif /* LIBCALENDAR_TST_COMMON_H */
