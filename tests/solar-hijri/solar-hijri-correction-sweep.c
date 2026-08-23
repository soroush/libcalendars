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

/*
 * Measures what happens when the leap year decisions of the arithmetic rule
 * are pinned to the official Iranian table one disagreement at a time.
 *
 * This is a measurement, not a pass or fail test.  Pinning a leap year is not
 * a local edit: making a year longer or shorter moves every Nowruz after it,
 * so a correction that is applied halfway through can leave the calendar in a
 * worse state than no correction at all.  The sweep makes that visible before
 * any of it is committed to the library.
 *
 * The correction model under test is the one a real fix would use.  A pinned
 * year e carries a delta of +1 when the officials call it a leap year and the
 * arithmetic does not, and -1 in the other direction.  Leap years and year
 * starts are then both derived from the same pin set, so they cannot drift
 * apart:
 *
 *   corrected_is_leap (y) = arithmetic_is_leap (y) XOR pinned (y)
 *   corrected_nowruz (y)  = arithmetic_nowruz (y)
 *                             + sum of delta (e) for pinned e < y
 *
 * The invariant that ties the two together, and the thing worth watching, is
 *
 *   corrected_nowruz (y + 1) - corrected_nowruz (y)
 *       == 366 if corrected_is_leap (y) else 365
 *
 * A pin set that satisfies it everywhere is a usable calendar; one that does
 * not is broken no matter how many individual dates it happens to get right.
 */

#include "ground-truth.h"

#include <libcalendars/cl-gregorian.h>
#include <libcalendars/cl-solar-hijri.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The uncorrected arithmetic rule, reproduced here on purpose.
 *
 * This program measures the distance between the 2820 year rule and the
 * decrees, so it has to keep hold of the rule in its raw form. The library no
 * longer offers it: sh_is_leap now answers for the calendar in civil use, and
 * asking it would make the sweep report that there is nothing to measure.
 * The constants are the same ones cl-solar-hijri.c is built on.
 */
#define LEAP_RATIO (683.0 / 2820.0)
#define SH_EPOCH 2121446L
#define SH_CYCLE_DAYS 1029983L
#define SH_CYCLE_YEARS 2820
#define SH_YEAR_LENGTH 365.24219858156028368

/* Integer remainder rather than a floating point fraction, for the reason
   given in cl-solar-hijri.c: the fraction is negative before year -2346 and
   rounds the wrong way where the quotient lands on the threshold. */
static int
arithmetic_is_leap (int year)
{
  const int r = (year + 2346) * 683 % SH_CYCLE_YEARS;
  return (r < 0 ? r + SH_CYCLE_YEARS : r) < 683 ? 1 : 0;
}

static int32_t
arithmetic_nowruz (int year)
{
  int32_t era = (year - 475) / SH_CYCLE_YEARS;
  int32_t y_c = 0;
  if ((year - 475) < 0)
    {
      --era;
    }
  y_c = (year - 475) - era * SH_CYCLE_YEARS;
  return (int32_t)SH_EPOCH + era * SH_CYCLE_DAYS
         + (int32_t)floor (y_c * SH_YEAR_LENGTH);
}

typedef struct pin_t
{
  int year;
  int delta; /* +1 when the officials add a day, -1 when they remove one */
} pin;

static int
official_is_leap (const sh_ground_truth_row *rows, size_t count, int year)
{
  size_t i = 0;
  for (i = 0; i < count; ++i)
    {
      if (rows[i].sh_year == year)
        {
          return sh_ground_truth_is_leap (&rows[i]);
        }
    }
  return -1;
}

static uint32_t
official_nowruz (const sh_ground_truth_row *row)
{
  uint32_t jdn = 0;
  gr_to_jdn (&jdn, (int16_t)row->gr_year, (uint8_t)row->gr_month,
             (uint16_t)row->gr_day);
  return jdn;
}

/* Sum of the deltas of every pin that lands strictly before the given year. */
static int
cumulative_offset (const pin *pins, size_t applied, int year)
{
  int offset = 0;
  size_t i = 0;
  for (i = 0; i < applied; ++i)
    {
      if (pins[i].year < year)
        {
          offset += pins[i].delta;
        }
    }
  return offset;
}

static int
is_pinned (const pin *pins, size_t applied, int year)
{
  size_t i = 0;
  for (i = 0; i < applied; ++i)
    {
      if (pins[i].year == year)
        {
          return 1;
        }
    }
  return 0;
}

static int
corrected_is_leap (const pin *pins, size_t applied, int year)
{
  const int arithmetic = arithmetic_is_leap (year);
  return is_pinned (pins, applied, year) ? !arithmetic : arithmetic;
}

/*
 * How far the year sits from the nearest leap decision boundary, in units of
 * the leap ratio.  The arithmetic rule calls a year leap when the fractional
 * part of (year + 2346) * 683 / 2820 falls below the ratio, so a year whose
 * fractional part sits just inside or just outside that window is one where
 * the observed equinox can easily land on the other side of noon in Tehran.
 * Those are exactly the years the officials are free to decide differently.
 */
static double
boundary_distance (int year)
{
  double integral = 0.0;
  const double frac = modf ((year + 2346) * LEAP_RATIO, &integral);
  const double below = frac; /* distance up from the window start */
  const double above
      = LEAP_RATIO - frac; /* distance down from the window end */
  double best = below < 0.0 ? -below : below;
  double other = above < 0.0 ? -above : above;
  double wrap = 1.0 - frac; /* distance up to the next window start */
  if (other < best)
    {
      best = other;
    }
  if (wrap < best)
    {
      best = wrap;
    }
  return best;
}

/*
 * The same metrics, read straight off the library instead of off the model.
 * If the two disagree, the shipped correction is not the one measured here.
 */
static void
measure_library (const sh_ground_truth_row *rows, size_t count)
{
  size_t i = 0;
  size_t leap_mismatches = 0;
  size_t nowruz_mismatches = 0;
  size_t invariant_violations = 0;
  int min_drift = 0;
  int max_drift = 0;

  for (i = 0; i < count; ++i)
    {
      const int year = rows[i].sh_year;
      const int leap = sh_is_leap ((int16_t)year) ? 1 : 0;
      uint32_t nowruz = 0;
      int32_t drift = 0;
      sh_to_jdn (&nowruz, (int16_t)year, 1, 1);
      drift = (int32_t)nowruz - (int32_t)official_nowruz (&rows[i]);

      if (leap != sh_ground_truth_is_leap (&rows[i]))
        {
          ++leap_mismatches;
        }
      if (drift != 0)
        {
          ++nowruz_mismatches;
        }
      if (drift < min_drift)
        {
          min_drift = (int)drift;
        }
      if (drift > max_drift)
        {
          max_drift = (int)drift;
        }

      if (i + 1 < count && rows[i + 1].sh_year == year + 1)
        {
          uint32_t next = 0;
          sh_to_jdn (&next, (int16_t)(year + 1), 1, 1);
          if ((int32_t)next - (int32_t)nowruz != (leap ? 366 : 365))
            {
              ++invariant_violations;
            }
        }
    }

  printf ("%-14s %6lu %10lu %8d %8d %12lu\n", "as built",
          (unsigned long)leap_mismatches, (unsigned long)nowruz_mismatches,
          min_drift, max_drift, (unsigned long)invariant_violations);
}

static void
measure (const sh_ground_truth_row *rows, size_t count, const pin *pins,
         size_t applied, const char *label)
{
  size_t i = 0;
  size_t leap_mismatches = 0;
  size_t nowruz_mismatches = 0;
  size_t invariant_violations = 0;
  int min_drift = 0;
  int max_drift = 0;
  int seen = 0;

  for (i = 0; i < count; ++i)
    {
      const int year = rows[i].sh_year;
      const int official_leap = sh_ground_truth_is_leap (&rows[i]);
      const int leap = corrected_is_leap (pins, applied, year);
      const int32_t drift = arithmetic_nowruz (year)
                            + cumulative_offset (pins, applied, year)
                            - (int32_t)official_nowruz (&rows[i]);

      if (leap != official_leap)
        {
          ++leap_mismatches;
        }
      if (drift != 0)
        {
          ++nowruz_mismatches;
        }
      if (!seen || drift < min_drift)
        {
          min_drift = (int)drift;
        }
      if (!seen || drift > max_drift)
        {
          max_drift = (int)drift;
        }
      seen = 1;

      /* The invariant only makes sense where the next year is also known. */
      if (i + 1 < count && rows[i + 1].sh_year == year + 1)
        {
          const int32_t span = arithmetic_nowruz (year + 1)
                               + cumulative_offset (pins, applied, year + 1)
                               - arithmetic_nowruz (year)
                               - cumulative_offset (pins, applied, year);
          if (span != (leap ? 366 : 365))
            {
              ++invariant_violations;
            }
        }
    }

  printf ("%-14s %6lu %10lu %8d %8d %12lu\n", label,
          (unsigned long)leap_mismatches, (unsigned long)nowruz_mismatches,
          min_drift, max_drift, (unsigned long)invariant_violations);
}

int
main (int argc, char **argv)
{
  static sh_ground_truth_row rows[SH_GROUND_TRUTH_MAX_ROWS];
  static pin pins[SH_GROUND_TRUTH_MAX_ROWS];
  const char *path = sh_ground_truth_path (argc, argv);
  const size_t count
      = sh_ground_truth_load (path, rows, SH_GROUND_TRUTH_MAX_ROWS);
  size_t candidates = 0;
  size_t i = 0;
  char label[32];

  /* Collect the disagreements in year order.  They are derived from the
     table rather than written down here, so the sweep follows the data. */
  for (i = 0; i < count; ++i)
    {
      const int official_leap = sh_ground_truth_is_leap (&rows[i]);
      if (official_leap != arithmetic_is_leap (rows[i].sh_year))
        {
          pins[candidates].year = rows[i].sh_year;
          pins[candidates].delta = official_leap ? 1 : -1;
          ++candidates;
        }
    }

  printf ("Ground truth: %s\n", path);
  printf ("Years %d to %d, %lu rows, %lu leap year disagreements\n\n",
          rows[0].sh_year, rows[count - 1].sh_year, (unsigned long)count,
          (unsigned long)candidates);

  printf ("Disagreements, with the distance of each year from the leap "
          "decision boundary\n");
  printf ("%6s %10s %10s %8s %14s\n", "year", "official", "library", "delta",
          "boundary");
  for (i = 0; i < candidates; ++i)
    {
      const int year = pins[i].year;
      printf ("%6d %10s %10s %+8d %14.2e\n", year,
              official_is_leap (rows, count, year) ? "leap" : "normal",
              arithmetic_is_leap (year) ? "leap" : "normal", pins[i].delta,
              boundary_distance (year));
    }
  printf ("\n");

  printf ("Applying the disagreements one at a time, in year order\n");
  printf ("%-14s %6s %10s %8s %8s %12s\n", "pinned", "leap", "nowruz", "min",
          "max", "invariant");
  printf ("%-14s %6s %10s %8s %8s %12s\n", "", "wrong", "wrong", "drift",
          "drift", "violations");

  measure (rows, count, pins, 0, "none");
  for (i = 0; i < candidates; ++i)
    {
      sprintf (label, "%d", pins[i].year);
      measure (rows, count, pins, i + 1, label);
    }

  printf ("\n");
  printf ("Applying them as complete pairs\n");
  printf ("%-14s %6s %10s %8s %8s %12s\n", "pinned", "leap", "nowruz", "min",
          "max", "invariant");
  printf ("%-14s %6s %10s %8s %8s %12s\n", "", "wrong", "wrong", "drift",
          "drift", "violations");

  measure (rows, count, pins, 0, "none");
  for (i = 1; i < candidates; i += 2)
    {
      sprintf (label, "through %d", pins[i].year);
      measure (rows, count, pins, i + 1, label);
    }

  printf ("\n");
  printf ("The library as it is built now, for comparison\n");
  printf ("%-14s %6s %10s %8s %8s %12s\n", "", "leap", "nowruz", "min", "max",
          "invariant");
  printf ("%-14s %6s %10s %8s %8s %12s\n", "", "wrong", "wrong", "drift",
          "drift", "violations");
  measure_library (rows, count);

  return EXIT_SUCCESS;
}
