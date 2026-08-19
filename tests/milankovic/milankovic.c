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

#include "calendar-arithmetic.h"

#include <libcalendars/cl-gregorian.h>
#include <libcalendars/cl-milankovic.h>

#include <assert.h>
#include <stdlib.h>

int
main (void)
{
  const test_context ctx = {
    .to_jdn = &ml_to_jdn,
    .from_jdn = &jdn_to_ml,
    .to_gr = &ml_to_gr,
    .from_gr = &gr_to_ml,
    .jdn_to_gr = &jdn_to_gr,
    .min_jd = 0,
    .max_jd = 2488069,
  };

  test_julian_day (&ctx);
  test_gregorian_calendar (&ctx);
}