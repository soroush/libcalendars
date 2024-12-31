/*
 * Copyright (C) 2021-2025 - Soroush Rabiei, <soroush.rabiei@gmail.com>
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

#include <libcalendars/cl-solar-hijri.h>
#include <libcalendars/cl-gregorian.h>
#include <gtest/gtest.h>

#include "calendar-arithmetic.hpp"

TEST_F(CalendarArithmetic, JulianDayConversion) {
    SetRange(0, 2488069);
    JulianDay(&jdn_to_sh, &sh_to_jdn);
}

TEST_F(CalendarArithmetic, GregorianConversion) {
    SetRange(0, 2488069);
    Gregorian(&jdn_to_gr, &sh_to_gr, &gr_to_sh);
}
