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

#include <gtest/gtest.h>
#include <functional>

class CalendarArithmetic : public ::testing::Test {
protected:
    using jdn_to_calendar = std::function<void(uint32_t, int16_t*, uint8_t*, uint16_t*)>;
    using calendar_to_jdn = std::function<void(uint32_t*, int16_t, uint8_t, uint16_t)>;
    using calendar_to_calendar = std::function<void(int16_t, uint8_t, uint16_t, int16_t*, uint8_t*, uint16_t*)>;

    CalendarArithmetic();

    void SetRange(uint32_t min_jdn, uint32_t max_jdn);
    void JulianDay(jdn_to_calendar, calendar_to_jdn);
    void Gregorian(jdn_to_calendar, calendar_to_calendar, calendar_to_calendar);

private:
    uint32_t min_jdn;
    uint32_t max_jdn;
};
