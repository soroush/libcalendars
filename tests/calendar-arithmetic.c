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
#include <assert.h>
#include <libcalendars/cl-gregorian.h>
#include <stdint.h>
#include <stdio.h>

void
test_julian_day (const test_context *const ctx)
{
  assert (ctx);
  int16_t year;
  uint8_t month;
  uint16_t day;
  uint32_t out_jd;
  for (uint32_t in_jd = ctx->min_jd; in_jd < ctx->max_jd; in_jd++)
    {
      ctx->from_jdn (in_jd, &year, &month, &day);
      ctx->to_jdn (&out_jd, year, month, day);
      assert (in_jd == out_jd);
    }
}

void
test_gregorian_calendar (const test_context *const ctx)
{
  assert (ctx);

  int16_t year;
  uint8_t month;
  uint16_t day;
  int16_t gyi;
  uint8_t gmi;
  uint16_t gdi;
  int16_t gyo;
  uint8_t gmo;
  uint16_t gdo;

  for (uint32_t in_jd = ctx->min_jd; in_jd < ctx->max_jd; in_jd++)
    {

      ctx->jdn_to_gr (in_jd, &gyi, &gmi, &gdi);
      ctx->from_gr (gyi, gmi, gdi, &year, &month, &day);
      ctx->to_gr (year, month, day, &gyo, &gmo, &gdo);
      assert (gyi == gyo);
      assert (gmi == gmo);
      assert (gdi == gdo);
    }
}

void
test_continuity (const test_context *const ctx)
{
  assert (ctx);
  uint16_t days_in_year = 0;
  uint16_t days_in_month = 0;
  int16_t year;
  uint8_t month;
  uint16_t day;

  ctx->from_jdn (ctx->min_jd, &year, &month, &day);

  for (uint32_t in_jd = ctx->min_jd + 1; in_jd < ctx->max_jd; in_jd++)
    {
      int16_t new_year;
      uint8_t new_month;
      uint16_t new_day;
      ctx->from_jdn (in_jd, &new_year, &new_month, &new_day);
      if (new_year == year && new_month == month && new_day == day + 1)
        {
          // Most common case. Continue counting
          if (days_in_year)
            days_in_year++;
          if (days_in_month)
            days_in_month++;
        }
      else if (new_year == year && new_month == month + 1 && new_day == 1)
        {
          // Same year, start of the new month
          if (days_in_month)
            {
              if (ctx->days_in_month (month, year) != days_in_month)
                {
                  printf ("Number of days in month is wrong! Date: "
                          "%04d-%02d-%02d\n"
                          "Counted days since start of the month: %04d\n",
                          year, month, day, days_in_month);
                }
              // assert(ctx->days_in_month(month, year) == days_in_month);
            }
          days_in_month = 1;
          if (days_in_year)
            days_in_year++;
        }
      else if (new_year == year + 1 && new_month == 1 && new_day == 1)
        {
          // In case, we were counting before, check for the days in year and
          // mount
          if (days_in_year)
            {
              if (ctx->days_in_year (year) != days_in_year)
                {
                  printf (
                      "Number of days in year is wrong! Date: %04d-%02d-%02d\n"
                      "Counted days since start of the year: %04d\n",
                      year, month, day, days_in_year);
                }
              assert (ctx->days_in_year (year) == days_in_year);
            }
          if (days_in_month)
            {
              if (ctx->days_in_month (month, year) != days_in_month)
                {
                  printf ("Number of days in month is wrong! Date: "
                          "%04d-%02d-%02d\n"
                          "Counted days since start of the month: %04d\n",
                          year, month, day, days_in_month);
                }
              assert (ctx->days_in_month (month, year) == days_in_month);
            }
          // In case we were not counting, Start counting days in the year and
          // month
          days_in_year = 1;
          days_in_month = 1;
        }
      else
        {
          // Should not happen
          // abort();
        }
      year = new_year;
      month = new_month;
      day = new_day;
    }
}