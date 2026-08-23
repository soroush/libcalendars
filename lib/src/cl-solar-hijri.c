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
#include <libcalendars/cl-gregorian.h>
#include <libcalendars/cl-solar-hijri.h>
#include <math.h>
#include <stddef.h>

/* Constants */

/* Number of days in a cycle */
static const int32_t cycle_days = 1029983;
/* Number of years in a cycle */
static const uint16_t cycle_years = 2820;
/* 365 + leapRatio */
static const double year_length = 365.24219858156028368;
// static const double year_length = 365.242374;
// static const double year_length = 365.2421875;
/* 475/01/01 AP, start of 2820 cycle */
static const uint32_t hijri_shamsi_epoch = 2121446;
/* Number of leap years in a cycle */
static const int32_t cycle_leap_years = 683;

/*
 * The calendar in civil use in Iran is not the arithmetic calendar.  Leap
 * years are settled by observation of the vernal equinox at the reference
 * meridian and, where the observation is close to noon, by decree.  On a
 * handful of years the decree placed the leap year one step away from where
 * the 2820 year rule puts it.
 *
 * Each entry below is such a displacement: `from` is the year the arithmetic
 * rule makes a leap year, `to` is the year the officials made one instead.
 * The two are always adjacent, so a swap neither creates nor destroys a day
 * and the calendar returns to the arithmetic year start immediately after it.
 *
 * These are decrees, not a pattern.  The years cannot be derived from the
 * rule: of the years that sit closest to the leap decision boundary, some
 * were moved and some were not.  Outside the range covered here no decree was
 * issued, and the arithmetic rule stands on its own.
 */
static const struct sh_leap_swap_t
{
  int16_t from;
  int16_t to;
} sh_leap_swaps[] = { { 1209, 1210 },
                      { 1242, 1243 },
                      { 1275, 1276 },
                      { 1437, 1436 },
                      { 1470, 1469 } };

static const size_t sh_leap_swap_count
    = sizeof (sh_leap_swaps) / sizeof (sh_leap_swaps[0]);

/*
 * Returns 1 when a decree forces the year to be a leap year, -1 when it
 * forces it to be a normal one, and 0 when the arithmetic rule is left alone.
 */
static int
sh_leap_correction (int16_t year)
{
  size_t i = 0;
  for (i = 0; i < sh_leap_swap_count; ++i)
    {
      if (year == sh_leap_swaps[i].to)
        {
          return 1;
        }
      if (year == sh_leap_swaps[i].from)
        {
          return -1;
        }
    }
  return 0;
}

/*
 * Returns the number of days the start of the given year moves by, which is
 * the running total of the days added and removed by every decree that falls
 * before it.  Because the two years of a swap are adjacent the total is back
 * to zero one year later, so only the later year of each swap ever starts on
 * a different day than the arithmetic rule says.
 */
static int
sh_nowruz_correction (int16_t year)
{
  int offset = 0;
  size_t i = 0;
  for (i = 0; i < sh_leap_swap_count; ++i)
    {
      if (sh_leap_swaps[i].from < year)
        {
          --offset;
        }
      if (sh_leap_swaps[i].to < year)
        {
          ++offset;
        }
    }
  return offset;
}

/*
 * The leap rule on the astronomical scale, where the year before 1 AP is year
 * zero. Everything inside this file works in that numbering, so the
 * conversions call this directly and the public sh_is_leap shifts into it.
 */
static uint8_t
sh_is_leap_a (int16_t year)
{
  const int correction = sh_leap_correction (year);
  if (correction)
    {
      return correction > 0 ? 1 : 0;
    }
  /*
   * A year is a leap year when the fractional part of
   * (year + 2346) * 683 / 2820 falls below 683 / 2820, which as an integer
   * remainder is simply
   *
   *   ((year + 2346) * 683) mod 2820 < 683.
   *
   * The remainder form is not a micro optimisation, it is the only form that
   * is correct. Taking the fraction in floating point fails twice. For years
   * before -2346 the product is negative and so is the fraction modf hands
   * back, which is always below the threshold, so every one of those years
   * was reported as a leap year. And where the quotient lands exactly on the
   * threshold, which happens at year 475 and at the same position in every
   * cycle, rounding drops it just under and the year disagrees with the year
   * start that fdoy_c computes for it.
   *
   * mod() gives a non-negative remainder, so both cases fall out.
   */
  return mod ((year + 2346) * (int)cycle_leap_years, (int)cycle_years)
                 < cycle_leap_years
             ? 1
             : 0;
}

/* Month length on the astronomical scale. */
static uint8_t
sh_days_in_month_a (uint8_t month, int16_t year)
{
  if (month > 0 && month <= 12)
    {
      return month < 7 ? 31 : month < 12 || sh_is_leap_a (year) ? 30 : 29;
    }

  return 0;
}

/* Year length on the astronomical scale. */
static uint16_t
sh_days_in_year_a (int16_t year)
{
  return sh_is_leap_a (year) ? 366 : 365;
}

LIBCALENDAR_API
uint8_t
sh_is_leap (int16_t year)
{
  /* The calendar has no year zero. Shift negative years onto the astronomical
     scale, on which 1 BP is year 0, before applying the leap rule. */
  if (year < 0)
    {
      ++year;
    }
  return sh_is_leap_a (year);
}

LIBCALENDAR_API
uint8_t
sh_days_in_month (uint8_t month, int16_t year)
{
  if (month > 0 && month <= 12)
    {
      return month < 7 ? 31 : month < 12 || sh_is_leap (year) ? 30 : 29;
    }

  return 0;
}

static int16_t
cycle (uint32_t jdn)
{
  const int32_t offset = jdn - hijri_shamsi_epoch;
  int16_t cycle_no = offset / cycle_days;
  if (offset < 0)
    {
      --cycle_no;
    }
  return cycle_no;
}

LIBCALENDAR_API
uint16_t
sh_days_in_year (int16_t year)
{
  return sh_is_leap (year) ? 366 : 365;
}

LIBCALENDAR_API uint8_t
sh_month_in_year (int16_t year)
{
  return 12;
}

LIBCALENDAR_API uint8_t
sh_is_valid (int16_t year, uint8_t month, uint16_t day)
{
  if (year < 0)
    ++year;
  if (day > 0 && day <= sh_days_in_month_a (month, year))
    {
      return 1;
    }
  return 0;
}

static uint32_t
cycle_start (uint32_t jdn)
{
  const int16_t era = cycle (jdn);
  const uint32_t start = hijri_shamsi_epoch + era * cycle_days;
  return start;
}

static uint32_t
fdoy_c (int year, int cycleNo)
{
  const double d_c = (year * year_length); /* Day in cycle */
  /* First day of year in a cycle */
  const uint32_t fdoy_c = (uint32_t)(floor (d_c));
  return hijri_shamsi_epoch + cycleNo * cycle_days + fdoy_c;
}

static uint32_t
fdoy (int year)
{
  /* Cycle number */
  int16_t c = year / cycle_years;
  /* First day of year in a cycle */
  uint32_t fdoy_c;
  /* Day number in cycle */
  double d_c;
  year -= 475;
  if (year < 0)
    {
      c--;
    }
  year -= (c * cycle_years);
  d_c = (year * year_length);
  fdoy_c = (uint32_t)(floor (d_c));
  return hijri_shamsi_epoch + c * cycle_days + fdoy_c;
}

/*
 * First day of the given year, with the decreed displacements applied.  Both
 * directions of the conversion go through this, so the leap year decisions
 * and the year starts cannot drift apart.  The year is expected in
 * astronomical numbering, the way sh_to_jdn holds it once year zero has been
 * folded in.
 */
static int32_t
sh_nowruz_jdn (int16_t year)
{
  int16_t era = (year - 475) / cycle_years;
  int32_t y_c = 0;
  if ((year - 475) < 0)
    {
      --era;
    }
  y_c = (year - 475) - era * cycle_years;
  return (int32_t)fdoy_c (y_c, era) + sh_nowruz_correction (year);
}

LIBCALENDAR_API
void
sh_to_jdn (uint32_t *jd, int16_t year, uint8_t month, uint16_t day)
{
  /* Adjust the offset of year 0 */
  int32_t d_y = 0;
  int32_t f_d = 0;
  size_t i = 0;
  if (year < 0)
    {
      ++year;
    }
  f_d = sh_nowruz_jdn (year);
  d_y = 0;
  for (i = 1; i < month; ++i)
    {
      d_y += sh_days_in_month_a (i, year);
    }
  d_y += day;
  *jd = f_d + d_y - 1;
}

LIBCALENDAR_API
void
jdn_to_sh (uint32_t jd, int16_t *year, uint8_t *month, uint16_t *day)
{
  const int c = cycle (jd);
  const int16_t y_c = (int16_t)(floor ((jd - cycle_start (jd)) / year_length));
  int16_t y = y_c + 475 + c * 2820;
  int32_t start = sh_nowruz_jdn (y);
  uint16_t d = 0;
  uint8_t m = 0;
  /* The estimate above comes from the mean year length and ignores the
     decrees, so it can land one year off on either side. Walk it back onto
     the year that actually contains the day. */
  while ((int32_t)jd < start)
    {
      --y;
      start = sh_nowruz_jdn (y);
    }
  while ((int32_t)jd >= start + sh_days_in_year_a (y))
    {
      ++y;
      start = sh_nowruz_jdn (y);
    }
  d = (uint16_t)((int32_t)jd - start + 1);
  for (m = 1; m < 12; ++m)
    {
      if (d > sh_days_in_month_a (m, y))
        {
          d -= sh_days_in_month_a (m, y);
        }
      else
        {
          break;
        }
    }
  /* Everything above works in astronomical numbering, the way sh_to_jdn holds
     the year. Step over year zero only once the day of the year has been
     spent, or the month lengths get taken from the neighbouring year. */
  if (y <= 0)
    {
      y--;
    }
  *year = y;
  *month = m;
  *day = d;
}

LIBCALENDAR_API
void
sh_to_gr (int16_t jyear, uint8_t jmonth, uint16_t jday, int16_t *gyear,
          uint8_t *gmonth, uint16_t *gday)
{
  uint32_t jdn = 0;
  sh_to_jdn (&jdn, jyear, jmonth, jday);
  jdn_to_gr (jdn, gyear, gmonth, gday);
}

LIBCALENDAR_API
void
gr_to_sh (int16_t gyear, uint8_t gmonth, uint16_t gday, int16_t *jyear,
          uint8_t *jmonth, uint16_t *jday)
{
  uint32_t jdn = 0;
  gr_to_jdn (&jdn, gyear, gmonth, gday);
  jdn_to_sh (jdn, jyear, jmonth, jday);
}
