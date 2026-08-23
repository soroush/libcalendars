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

#ifndef LIBCALENDARS_TEST_SOLAR_HIJRI_GROUND_TRUTH_H
#define LIBCALENDARS_TEST_SOLAR_HIJRI_GROUND_TRUTH_H

#include <stddef.h>
#include <stdint.h>

/*
 * The Solar Hijri calendar in official use in Iran is not defined by an
 * arithmetic rule.  Leap years are fixed by observation of the vernal
 * equinox at the reference meridian and, in practice, by decisions of the
 * parliament.  The table read here is the published official mapping and is
 * treated as the ground truth: where the library disagrees with it, the
 * library is wrong about the civil calendar even though its arithmetic is
 * self consistent.
 *
 * Each row gives the first day of a Solar Hijri year (Nowruz), the two leap
 * flags assigned to that year, and the Gregorian date the same day falls on.
 * A year is a leap year when either flag is set; the flags are never both
 * set at the same time.
 */
typedef struct sh_ground_truth_row_t
{
  int sh_year;
  int sh_month;
  int sh_day;
  int leap_4; /* year is a leap year of the four year cycle */
  int leap_5; /* year is a leap year of the five year cycle */
  int gr_year;
  int gr_month;
  int gr_day;
} sh_ground_truth_row;

/* Enough room for the published table with a wide margin. */
#define SH_GROUND_TRUTH_MAX_ROWS 1024

/*
 * Returns the path of the ground truth CSV.  The build passes it as the
 * first argument; the compiled in path is used as a fallback so the test can
 * also be run by hand from the build tree.
 */
const char *sh_ground_truth_path (int argc, char **argv);

/*
 * Reads the CSV into rows, skipping the header line, and returns the number
 * of rows read.  Aborts if the file cannot be opened or a line cannot be
 * parsed, since a test that silently reads nothing would always pass.
 */
size_t sh_ground_truth_load (const char *path, sh_ground_truth_row *rows,
                             size_t capacity);

/* True when the official table marks the year of this row as a leap year. */
int sh_ground_truth_is_leap (const sh_ground_truth_row *row);

#endif /* LIBCALENDARS_TEST_SOLAR_HIJRI_GROUND_TRUTH_H */
