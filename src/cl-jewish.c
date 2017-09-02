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
int jw_is_leap(int16_t year) {
}

LIBCALENDAR_API
int jw_days_in_month(uint8_t month, int16_t year) {
}

LIBCALENDAR_API
uint16_t jw_days_in_year(int16_t year) {
}

static inline int32_t q(int32_t x) {
    return clm_floor_div(clm_floor_div(235 * x + 1, 19), 1095);
}

static inline int32_t r(int32_t x) {
    return clm_mod(clm_floor_div(235 * x + 1, 19), 1095);
}

static inline int32_t v1(int32_t x) {
    const int32_t c1 = clm_floor_div(235 * x + 1, 19);
    const int32_t qx = clm_floor_div(c1, 1095);
    return 32336 * qx
           + clm_floor_div(15 * qx + 765433 * clm_mod(c1, 1095) + 12084, 25920);
}

static inline int32_t v2(int32_t x) {
    return v1(x) + clm_mod(clm_floor_div(6 * clm_mod(v1(x), 7), 7), 2);
}

static inline int32_t L2(int32_t x) {
    return v2(x + 1) - v2(x);
}

static inline int32_t v3(int32_t x) {
    return 2 * clm_mod(clm_floor_div(L2(x) + 19, 15), 2);
}

static inline int32_t v4(int32_t x) {
    return clm_mod(clm_floor_div(L2(x - 1) + 7, 15), 2);
}

static inline int32_t c2(int32_t x) {
    return v2(x) + v3(x) + v4(x);
}

static inline int32_t L(int32_t x) {
    return c2(x + 1) - c2(x);
}

static inline int32_t c8(int32_t x) {
    return clm_mod(clm_floor_div(L(x) + 7, 2), 15);
}

static inline int32_t c9(int32_t x) {
    return -1 * clm_mod(clm_floor_div(385 - L(x), 2), 15);
}

static inline int32_t c3(int32_t x) {
    return clm_floor_div(384 * x + 7, 13)
           + c8(x) * clm_floor_div(x + 4, 12)
           + c9(x) * clm_floor_div(x + 3, 12);
}

static inline int32_t c4(int32_t x, int32_t y) {

    const int32_t c1 = clm_floor_div(235 * x + 1, 19);
    const int32_t qx = clm_floor_div(c1, 1095);
    const int32_t Ly = L(y);
    const int32_t rx = clm_mod(c1, 1095);
    const int32_t v1x = 32336 * qx
                        + clm_floor_div(15 * qx + 765433 * rx + 12084, 25920);
    return
        v1x
        + clm_mod(clm_floor_div(6 * clm_mod(v1x, 7), 7), 2)
        + 2 * clm_mod(clm_floor_div(L2(x) + 19, 15), 2)
        + clm_mod(clm_floor_div(L2(x - 1) + 7, 15), 2)
        + clm_floor_div(384 * y + 7, 13)
        + clm_mod(clm_floor_div(Ly + 7, 2), 15) * clm_floor_div(y + 4, 12)
        - clm_mod(clm_floor_div(385 - Ly, 2), 15) * clm_floor_div(y + 3, 12);
}

LIBCALENDAR_API
void jw_to_jdn(uint32_t* jd, int16_t year, uint8_t month, uint16_t day) {
    const int32_t j0 = 347998;
    const int32_t c0 = clm_floor_div(13 - month, 7);
    const int32_t x1 = year - 1 + c0;
    const int32_t x3 = month - 1;
    const int32_t z4 = day - 1;
    const int32_t qx = q(x1);
    *jd = j0 - 177
          + 32336 * qx
          + clm_floor_div(15 * qx + 765433 * r(x1) + 12084, 25920)
          + clm_mod(clm_floor_div(6 * clm_mod(v1(x1), 7), 7), 2)
          + 2 * clm_mod(clm_floor_div(L2(x1) + 19, 15), 2)
          + clm_mod(clm_floor_div(L2(x1 - 1) + 7, 15), 2)
          + clm_floor_div(384 * x3 + 7, 13)
          + clm_mod(clm_floor_div(L(x3) + 7, 2), 15) * clm_floor_div(x3 + 4, 12)
          - clm_mod(clm_floor_div(385 - L(x3), 2), 15)
          * clm_floor_div(x3 + 3, 12) + z4;
}

LIBCALENDAR_API
void jdn_to_jw(uint32_t jd, int16_t* year, uint8_t* month, uint16_t* day) {
    const int32_t y4 = jd - 347821;
    const int32_t q = clm_floor_div(y4, 1447);
    const int32_t r = clm_mod(y4, 1447);
    const int32_t y1_p = 49 * q
                         + clm_floor_div(23 * q + 25920 * r + 13835, 765433);
    const int32_t gamma_1 = y1_p + 1;
    const int32_t xi_1 = clm_floor_div(19 * gamma_1 + 17, 235);
    const int32_t mu_1 = gamma_1 - clm_floor_div(235 * xi_1 + 1, 19);
    const int32_t zeta_1 = y4 - c4(xi_1, mu_1);
    const int32_t gamma_2 = gamma_1 + clm_floor_div(zeta_1, 33);
    const int32_t xi_2 = clm_floor_div(19 * gamma_2 + 17, 235);
    const int32_t mu_2 = gamma_2 - clm_floor_div(235 * xi_2 + 1, 19);
    const int32_t zeta_2 = y4 - c4(xi_2, mu_2);
    const int32_t gamma_3 = gamma_2 + clm_floor_div(zeta_2, 33);
    const int32_t xi_3 = clm_floor_div(19 * gamma_3 + 17, 235);
    const int32_t mu_3 = gamma_3 - clm_floor_div(235 * xi_3 + 1, 19);
    const int32_t zeta_3 = y4 - c4(xi_3, mu_3);
    const int32_t c = clm_floor_div(12 - mu_3, 7);
    *year = xi_3 + 1 - c;
    *month = mu_3 + 1;
    *day = zeta_3 + 1;
}

LIBCALENDAR_API
void jw_to_gr(int16_t  jyear,  uint8_t jmonth,  uint16_t jday,
              int16_t* gyear, uint8_t* gmonth, uint16_t* gday) {
    uint32_t jdn = 0;
    jw_to_jdn(&jdn, jyear, jmonth, jday);
    jdn_to_gr(jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void gr_to_jw(int16_t  gyear,  uint8_t gmonth,  uint16_t gday,
              int16_t* jyear, uint8_t* jmonth, uint16_t* jday) {
    uint32_t jdn = 0;
    gr_to_jdn(&jdn, gyear, gmonth, gday);
    jdn_to_jw(jdn, jyear, jmonth, jday);
}
