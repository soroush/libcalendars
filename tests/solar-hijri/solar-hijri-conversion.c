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

/*
 * Converts every Nowruz in the official Iranian table in both directions and
 * compares the result with the published Gregorian date.  The arithmetic
 * calendar drifts one day from the civil one on some years, so this test is
 * expected to fail until that drift is handled separately.
 *
 * Both directions are checked independently: a wrong leap year decision can
 * shift one of them without shifting the other.  Every mismatch is reported
 * rather than aborting on the first one.
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
  size_t to_gr_mismatches = 0;
  size_t from_gr_mismatches = 0;

  for (i = 0; i < count; ++i)
    {
      const sh_ground_truth_row *row = &rows[i];
      int16_t gy = 0;
      uint8_t gm = 0;
      uint16_t gd = 0;
      int16_t sy = 0;
      uint8_t sm = 0;
      uint16_t sd = 0;

      sh_to_gr ((int16_t)row->sh_year, (uint8_t)row->sh_month,
                (uint16_t)row->sh_day, &gy, &gm, &gd);
      if (gy != row->gr_year || gm != row->gr_month || gd != row->gr_day)
        {
          ++to_gr_mismatches;
          printf ("sh_to_gr mismatch for %04d-%02d-%02d: official says "
                  "%04d-%02d-%02d, library says %04d-%02d-%02d\n",
                  row->sh_year, row->sh_month, row->sh_day, row->gr_year,
                  row->gr_month, row->gr_day, (int)gy, (int)gm, (int)gd);
        }

      gr_to_sh ((int16_t)row->gr_year, (uint8_t)row->gr_month,
                (uint16_t)row->gr_day, &sy, &sm, &sd);
      if (sy != row->sh_year || sm != row->sh_month || sd != row->sh_day)
        {
          ++from_gr_mismatches;
          printf ("gr_to_sh mismatch for %04d-%02d-%02d: official says "
                  "%04d-%02d-%02d, library says %04d-%02d-%02d\n",
                  row->gr_year, row->gr_month, row->gr_day, row->sh_year,
                  row->sh_month, row->sh_day, (int)sy, (int)sm, (int)sd);
        }
    }

  printf ("Checked %lu dates from %s, %lu sh_to_gr mismatches, %lu gr_to_sh "
          "mismatches\n",
          (unsigned long)count, path, (unsigned long)to_gr_mismatches,
          (unsigned long)from_gr_mismatches);

  return (to_gr_mismatches || from_gr_mismatches) ? EXIT_FAILURE
                                                  : EXIT_SUCCESS;
}
