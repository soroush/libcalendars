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
 * Compares the leap year decisions of the 2820 year arithmetic rule against
 * the official Iranian table.  The two do not agree everywhere, so this test
 * is expected to fail until the drift between the arithmetic calendar and the
 * civil one is handled separately.
 *
 * Every mismatch is reported rather than aborting on the first one, because
 * the shape of the disagreement is what matters here.
 */

#include "ground-truth.h"

#include <libcalendars/cl-solar-hijri.h>

#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
  static sh_ground_truth_row rows[SH_GROUND_TRUTH_MAX_ROWS];
  const char *path = sh_ground_truth_path (argc, argv);
  size_t count = sh_ground_truth_load (path, rows, SH_GROUND_TRUTH_MAX_ROWS);
  size_t i = 0;
  size_t mismatches = 0;

  for (i = 0; i < count; ++i)
    {
      const int expected = sh_ground_truth_is_leap (&rows[i]);
      const int actual = sh_is_leap ((int16_t)rows[i].sh_year) ? 1 : 0;
      if (expected != actual)
        {
          ++mismatches;
          printf ("Leap year mismatch for %04d: official says %s (L_4=%d, "
                  "L_5=%d), library says %s\n",
                  rows[i].sh_year, expected ? "leap" : "normal",
                  rows[i].leap_4, rows[i].leap_5, actual ? "leap" : "normal");
        }
    }

  printf ("Checked %lu years from %s, %lu leap year mismatches\n",
          (unsigned long)count, path, (unsigned long)mismatches);

  return mismatches ? EXIT_FAILURE : EXIT_SUCCESS;
}
