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

#include "cl-math.h"
#include <libcalendars/cl-egyptian.h>
#include <libcalendars/cl-gregorian.h>
#include <math.h>
#include <stdlib.h>

LIBCALENDAR_API
uint8_t
eg_is_leap (int16_t year)
{
  return 0;
}

LIBCALENDAR_API
uint8_t
eg_days_in_month (uint8_t month, int16_t year)
{
  if (month == 13)
    return 5;
  return 30;
}

LIBCALENDAR_API
uint16_t
eg_days_in_year (int16_t year)
{
  return 365;
}

LIBCALENDAR_API
uint8_t
eg_month_in_year (int16_t year)
{
  return 13;
}

LIBCALENDAR_API
uint8_t
eg_is_valid (int16_t year, uint8_t month, uint16_t day)
{
  if (day > 0 && day <= eg_days_in_month (month, year))
    {
      return 1;
    }
  return 0;
}

LIBCALENDAR_API
void
eg_to_jdn (uint32_t *jd, int16_t year, uint8_t month, uint16_t day)
{
  *jd = 365 * year + 30 * month + day + 1448242;
}

LIBCALENDAR_API
void
jdn_to_eg (uint32_t jd, int16_t *year, uint8_t *month, uint16_t *day)
{
  const int32_t y2 = jd - 1448638;
  const int32_t x2 = fdiv (y2, 365);
  const int32_t y1 = mod (y2, 365);
  *year = (int16_t)(x2 + 1);
  *month = (uint8_t)(fdiv (y1, 30) + 1);
  *day = (uint8_t)(mod (y1, 30) + 1);
}

LIBCALENDAR_API
void
eg_to_gr (int16_t jyear, uint8_t jmonth, uint16_t jday, int16_t *gyear,
          uint8_t *gmonth, uint16_t *gday)
{
  uint32_t jdn = 0;
  eg_to_jdn (&jdn, jyear, jmonth, jday);
  jdn_to_gr (jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void
gr_to_eg (int16_t gyear, uint8_t gmonth, uint16_t gday, int16_t *jyear,
          uint8_t *jmonth, uint16_t *jday)
{
  uint32_t jdn = 0;
  gr_to_jdn (&jdn, gyear, gmonth, gday);
  jdn_to_eg (jdn, jyear, jmonth, jday);
}
