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

#pragma once

#include <stdint.h>
#include <stdio.h>

typedef struct test_context_t
{
  void (*to_jdn) (uint32_t *, int16_t, uint8_t, uint16_t);
  void (*from_jdn) (uint32_t, int16_t *, uint8_t *, uint16_t *);
  void (*to_gr) (int16_t, uint8_t, uint16_t, int16_t *, uint8_t *, uint16_t *);
  void (*from_gr) (int16_t, uint8_t, uint16_t, int16_t *, uint8_t *,
                   uint16_t *);
  void (*jdn_to_gr) (uint32_t, int16_t *, uint8_t *, uint16_t *);
  uint8_t (*days_in_month) (uint8_t month, int16_t year);
  uint16_t (*days_in_year) (int16_t year);
  uint8_t (*month_in_year) (int16_t year);
  uint8_t (*is_valid) (int16_t year, uint8_t month, uint16_t day);
  uint32_t min_jd;
  uint32_t max_jd;
} test_context;

void test_julian_day (const test_context *const ctx);
void test_gregorian_calendar (const test_context *const ctx);
void test_continuity (const test_context *const ctx);