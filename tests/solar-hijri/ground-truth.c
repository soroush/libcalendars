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

#include "ground-truth.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef SH_GROUND_TRUTH_CSV
#define SH_GROUND_TRUTH_CSV "official-leap-years.csv"
#endif

const char *
sh_ground_truth_path (int argc, char **argv)
{
  if (argc > 1 && argv[1] && argv[1][0])
    {
      return argv[1];
    }
  return SH_GROUND_TRUTH_CSV;
}

static int
is_blank (const char *line)
{
  const char *p = line;
  while (*p)
    {
      if (*p != ' ' && *p != '\t' && *p != '\r' && *p != '\n')
        {
          return 0;
        }
      ++p;
    }
  return 1;
}

size_t
sh_ground_truth_load (const char *path, sh_ground_truth_row *rows,
                      size_t capacity)
{
  char line[256];
  size_t count = 0;
  unsigned long lineno = 0;
  FILE *file = fopen (path, "r");

  if (!file)
    {
      printf ("Cannot open the ground truth table: %s\n", path);
      abort ();
    }

  while (fgets (line, (int)sizeof (line), file))
    {
      sh_ground_truth_row row;
      ++lineno;
      if (is_blank (line))
        {
          continue;
        }
      if (lineno == 1)
        {
          /* Header line. */
          continue;
        }
      if (sscanf (line, "%d,%d,%d,%d,%d,%d,%d,%d", &row.sh_year, &row.sh_month,
                  &row.sh_day, &row.leap_4, &row.leap_5, &row.gr_year,
                  &row.gr_month, &row.gr_day)
          != 8)
        {
          printf ("Malformed ground truth row at %s:%lu: %s", path, lineno,
                  line);
          fclose (file);
          abort ();
        }
      if (row.leap_4 && row.leap_5)
        {
          printf ("Ground truth row at %s:%lu marks the year as leap in both "
                  "cycles at once\n",
                  path, lineno);
          fclose (file);
          abort ();
        }
      if (count == capacity)
        {
          printf ("Ground truth table at %s has more than %lu rows\n", path,
                  (unsigned long)capacity);
          fclose (file);
          abort ();
        }
      rows[count] = row;
      ++count;
    }

  fclose (file);

  if (count == 0)
    {
      printf ("Ground truth table at %s holds no rows\n", path);
      abort ();
    }

  return count;
}

int
sh_ground_truth_is_leap (const sh_ground_truth_row *row)
{
  return (row->leap_4 || row->leap_5) ? 1 : 0;
}
