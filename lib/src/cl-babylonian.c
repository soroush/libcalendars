/*
 * Copyright (C) 2021-2025 - Soroush Rabiei, <soroush.rabiei@gmail.com>
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
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "cl-math.h"
#include <libcalendars/cl-babylonian.h>
#include <libcalendars/cl-gregorian.h>
#include <math.h>
#include <stdlib.h>

LIBCALENDAR_API
uint8_t
ba_is_leap (int16_t year)
{
  const int16_t cycle = mod (year, 19);
  switch (cycle)
    {
    case 1:
    case 4:
    case 7:
    case 9:
    case 12:
    case 15:
    case 18:
      return 1;
    default:
      return 0;
    }
}

LIBCALENDAR_API
uint8_t
ba_days_in_month (uint8_t month, int16_t year)
{
  const int16_t cycle = mod (year, 19);
  uint8_t m0 = month;

  switch (cycle)
    {
    case 1:
    case 4:
    case 7:
    case 9:
    case 12:
    case 15:
      if (month == 13)
        m0--;
      break;
    case 18:
      if (month > 6)
        m0--;
      break;
    }

  if (mod (m0, 2) == 1)
    return 30;
  else
    return 29;
}

LIBCALENDAR_API
uint16_t
ba_days_in_year (int16_t year)
{
  if (ba_is_leap (year) == 1)
    return 383;
  else
    return 354;
}

LIBCALENDAR_API
uint8_t
ba_month_in_year (int16_t year)
{
  if (ba_is_leap (year) == 1)
    return 13;
  return 12;
}

LIBCALENDAR_API
uint8_t
ba_is_valid (int16_t year, uint8_t month, uint16_t day)
{
  if (day > 0 && day <= ba_days_in_month (month, year))
    {
      return 1;
    }
  return 0;
}

LIBCALENDAR_API
void
ba_to_jdn (uint32_t *jd, int16_t year, uint8_t month, uint16_t day)
{
  *jd = fdiv (6940 * (fdiv (235 * year + 13, 19) + month - 1), 235) + day
        + 1607174;
}

LIBCALENDAR_API
void
jdn_to_ba (uint32_t jd, int16_t *year, uint8_t *month, uint16_t *day)
{
  const uint32_t s = jd - 1607175;
  const div_t m1_omega1 = pdiv (235 * s + 234, 6940);
  const div_t j_omega2 = pdiv (19 * m1_omega1.quot + 5, 235);
  *day = fdiv (m1_omega1.rem, 235) + 1;
  *month = fdiv (j_omega2.rem, 19) + 1;
  *year = j_omega2.quot;
}

LIBCALENDAR_API
void
ba_to_gr (int16_t jyear, uint8_t jmonth, uint16_t jday, int16_t *gyear,
          uint8_t *gmonth, uint16_t *gday)
{
  uint32_t jdn = 0;
  ba_to_jdn (&jdn, jyear, jmonth, jday);
  jdn_to_gr (jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void
gr_to_ba (int16_t gyear, uint8_t gmonth, uint16_t gday, int16_t *jyear,
          uint8_t *jmonth, uint16_t *jday)
{
  uint32_t jdn = 0;
  gr_to_jdn (&jdn, gyear, gmonth, gday);
  jdn_to_ba (jdn, jyear, jmonth, jday);
}
