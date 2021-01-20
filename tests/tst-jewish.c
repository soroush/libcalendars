/*
 * Copyright 2021 - Soroush Rabiei, <soroush.rabiei@gmail.com>
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

#include <libcalendars/cl-jewish.h>
#include "tst-common.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int result;
    printf("TEST: Jewish Calendar...\n");
    result = tst_calendar(&jw_to_jdn, &jdn_to_jw, &jw_to_gr, &gr_to_jw, 0, 2488069);
    printf("%s: Jewish Calendar.\n", result == 0 ? "PASS" : "FAIL");
    return result;
}
