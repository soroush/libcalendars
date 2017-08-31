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

#include "cl-math.h"
#include <math.h>

div_t clm_pdiv(int d, int v) {
    div_t rv = div(d, v);
    if(rv.rem < 0) {
        if(v>0) {
            rv.quot -= 1;
            rv.rem += v;
        } else {
            rv.quot += 1;
            rv.rem -= v;
        }
    }
    return rv;
}

int clm_floor_div(int a, int b) {
    return floor((float)(a)/(float)(b));
}

int clm_mod(int a, int b) {
    return a - clm_floor_div(a, b);
}
