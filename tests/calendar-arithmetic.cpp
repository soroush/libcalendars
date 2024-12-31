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

#include "calendar-arithmetic.hpp"

CalendarArithmetic::CalendarArithmetic()
    : ::testing::Test()
    , min_jdn(0)
    , max_jdn(0)
{
}

void CalendarArithmetic::SetRange(uint32_t min_jdn_, uint32_t max_jdn_)
{
    this->min_jdn = min_jdn_;
    this->max_jdn = max_jdn_;
}

void CalendarArithmetic::JulianDay(CalendarArithmetic::jdn_to_calendar to_calendar, CalendarArithmetic::calendar_to_jdn to_jdn)
{
    ASSERT_NE(to_calendar, nullptr) << "`to_calendar` function not set.";
    ASSERT_NE(to_jdn, nullptr) << "`to_jdn` function not set.";
    uint32_t jdn = 0;
    uint32_t jdn2 = 0;
    for (jdn = min_jdn; jdn < max_jdn; ++jdn)
    {
        int16_t year;
        uint8_t month;
        uint16_t day;
        to_calendar(jdn, &year, &month, &day);
        to_jdn(&jdn2, year, month, day);
        ASSERT_EQ(jdn2, jdn);
    }
}

void CalendarArithmetic::Gregorian(CalendarArithmetic::jdn_to_calendar to_calendar,
    CalendarArithmetic::calendar_to_calendar cal_to_gr, 
    CalendarArithmetic::calendar_to_calendar gr_to_cal)
{
    uint32_t jdn = 0;
    uint32_t jdn2 = 0;
    for (jdn = min_jdn; jdn < max_jdn; ++jdn)
    {
        int16_t gy[2] = {0, 0};
        uint8_t gm[2] = {0, 0};
        uint16_t gd[2] = {0, 0};
        int16_t year;
        uint8_t month;
        uint16_t day;

        to_calendar(jdn, &gy[0], &gm[0], &gd[0]);
        gr_to_cal(gy[0], gm[0], gd[0], &year, &month, &day);
        cal_to_gr(year, month, day, &gy[1], &gm[1], &gd[1]);

        ASSERT_EQ(gy[0], gy[1]);
        ASSERT_EQ(gm[0], gm[1]);
        ASSERT_EQ(gd[0], gd[1]);
    }
}