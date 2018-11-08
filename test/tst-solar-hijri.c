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

#include "../src/cl-solar-hijri.h"
#include "tst-common.h"

void tst_time_zone() {

}

#ifdef _WIN32
DWORD WINAPI tst_solar_hijri(LPVOID param_arg) {
#else
int main(int argc, char *argv[]) {
#endif
    int result;
    printf("TEST: Solar Hijri Calendar...\n");
    result = tst_calendar(&sh_to_jdn, &jdn_to_sh, &sh_to_gr, &gr_to_sh, 0, 2488069);
    printf("%s: Solar Hijri Calendar.\n", result == 0 ? "PASS" : "FAIL");
    return result;
}
