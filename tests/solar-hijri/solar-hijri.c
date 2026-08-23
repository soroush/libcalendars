/*
 * Copyright (C) 2017-2026 Soroush Rabiei <soroush.rabiei@gmail.com>
 *
 * This file is part of libcalendars.
 *
 * libcalendars is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendars is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "calendar-arithmetic.h"

#include <libcalendars/cl-gregorian.h>
#include <libcalendars/cl-solar-hijri.h>

#include <assert.h>
#include <stdlib.h>

int
main (void)
{
  const test_context ctx = {
    .to_jdn = &sh_to_jdn,
    .from_jdn = &jdn_to_sh,
    .to_gr = &sh_to_gr,
    .from_gr = &gr_to_sh,
    .jdn_to_gr = &jdn_to_gr,
    .days_in_month = &sh_days_in_month,
    .days_in_year = &sh_days_in_year,
    .month_in_year = &sh_month_in_year,
    .min_jd = 0,
    .max_jd = 2488069,
  };

  test_julian_day (&ctx);
  test_gregorian_calendar (&ctx);
  test_continuity (&ctx);

  return EXIT_SUCCESS;
}