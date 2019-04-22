/*
 * Copyright 2017 - Soroush Rabiei, <soroush@ametisco.ir>
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
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "cl-calendars.h"
#include "cl-gregorian.h"
#include "cl-julian.h"
#include "cl-milankovic.h"
#include "cl-jewish.h"
#include "cl-islamic-civil.h"
#include "cl-solar-hijri.h"

LIBCALENDAR_API
uint8_t is_leap(uint8_t calendar, int16_t year) {
    switch(calendar) {
        case CAL_GREGORIAN:
            return gr_is_leap(year);
        case CAL_JULIAN:
            return ju_is_leap(year);
        case CAL_MILANKOVIC:
            return ml_is_leap(year);
        case CAL_ISLAMIC_CIVIL:
            return is_is_leap(year);
        case CAL_JEWSISH:
            return jw_is_leap(year);
        case CAL_SOLAR_HIJRI:
            return sh_is_leap(year);
        default:
            return 0;
    }
}

LIBCALENDAR_API uint8_t
days_in_month(uint8_t calendar, uint8_t month, int16_t year) {
    switch(calendar) {
        case CAL_GREGORIAN:
            return gr_days_in_month(month, year);
        case CAL_JULIAN:
            return ju_days_in_month(month, year);
        case CAL_MILANKOVIC:
            return ml_days_in_month(month, year);
        case CAL_ISLAMIC_CIVIL:
            return is_days_in_month(month, year);
        case CAL_JEWSISH:
            return jw_days_in_month(month, year);
        case CAL_SOLAR_HIJRI:
            return sh_days_in_month(month, year);
        default:
            return 0;
    }
}

LIBCALENDAR_API
uint16_t days_in_year(uint8_t calendar, int16_t year) {
    switch(calendar) {
        case CAL_GREGORIAN:
            return gr_days_in_year(year);
        case CAL_JULIAN:
            return ju_days_in_year(year);
        case CAL_MILANKOVIC:
            return ml_days_in_year(year);
        case CAL_ISLAMIC_CIVIL:
            return is_days_in_year(year);
        case CAL_JEWSISH:
            return jw_days_in_year(year);
        case CAL_SOLAR_HIJRI:
            return sh_days_in_year(year);
        default:
            return 0;
    }
}

LIBCALENDAR_API uint8_t month_in_year(uint8_t calendar, int16_t year) {
    switch(calendar) {
        case CAL_GREGORIAN:
            return gr_month_in_year(year);
        case CAL_JULIAN:
            return ju_month_in_year(year);
        case CAL_MILANKOVIC:
            return ml_month_in_year(year);
        case CAL_ISLAMIC_CIVIL:
            return is_month_in_year(year);
        case CAL_JEWSISH:
            return jw_month_in_year(year);
        case CAL_SOLAR_HIJRI:
            return sh_month_in_year(year);
        default:
            return 0;
    }
}

LIBCALENDAR_API uint8_t is_valid(uint8_t calendar,
                                 int16_t year, uint8_t month, uint16_t day) {
    switch(calendar) {
        case CAL_GREGORIAN:
            return gr_is_valid(year, month, day);
        case CAL_JULIAN:
            return ju_is_valid(year, month, day);
        case CAL_MILANKOVIC:
            return ml_is_valid(year, month, day);
        case CAL_ISLAMIC_CIVIL:
            return is_is_valid(year, month, day);
        case CAL_JEWSISH:
            return jw_is_valid(year, month, day);
        case CAL_SOLAR_HIJRI:
            return sh_is_valid(year, month, day);
        default:
            return 0;
    }
}

LIBCALENDAR_API void to_jdn(uint8_t calendar, uint32_t* jd,
                            int16_t year, uint8_t month, uint16_t day) {
    switch(calendar) {
        case CAL_GREGORIAN:
            gr_to_jdn(jd, year, month, day);
            break;
        case CAL_JULIAN:
            ju_to_jdn(jd, year, month, day);
            break;
        case CAL_MILANKOVIC:
            ml_to_jdn(jd, year, month, day);
            break;
        case CAL_ISLAMIC_CIVIL:
            is_to_jdn(jd, year, month, day);
            break;
        case CAL_JEWSISH:
            jw_to_jdn(jd, year, month, day);
            break;
        case CAL_SOLAR_HIJRI:
            sh_to_jdn(jd, year, month, day);
            break;
        default:
            *jd = 0;
            break;
    }
}

LIBCALENDAR_API void to_date(uint8_t calendar, uint32_t jd,
                             int16_t* year, uint8_t* month, uint16_t* day) {
    switch(calendar) {
        case CAL_GREGORIAN:
            jdn_to_gr(jd, year, month, day);
            break;
        case CAL_JULIAN:
            jdn_to_ju(jd, year, month, day);
            break;
        case CAL_MILANKOVIC:
            jdn_to_ml(jd, year, month, day);
            break;
        case CAL_ISLAMIC_CIVIL:
            jdn_to_is(jd, year, month, day);
            break;
        case CAL_JEWSISH:
            jdn_to_jw(jd, year, month, day);
            break;
        case CAL_SOLAR_HIJRI:
            jdn_to_sh(jd, year, month, day);
            break;
        default:
            *year = 0;
            *month = 0;
            *day = 0;
            break;
    }
}

LIBCALENDAR_API
void convert_date(uint8_t icalendar, uint8_t ocalendar,
                  int16_t iyear, uint8_t imonth, uint16_t iday,
                  int16_t* oyear, uint8_t* omonth, uint16_t* oday) {
    uint32_t jdn = 0;
    if(!is_valid(icalendar, iyear, imonth, iday)) {
        *oyear = 0;
        *omonth = 0;
        *oday = 0;
        return;
    }
    if(icalendar == ocalendar) {
        *oyear = iyear;
        *omonth = imonth;
        *oday = iday;
        return;
    }
    /* Handle exceptions: Pair of calendars that can be converted using more
     * optimized algorithms. For all other pairs, use jdn as an intermediate
     * variable to convert dates.
     */
    to_jdn(icalendar, &jdn, iyear, imonth, iday);
    to_date(ocalendar, jdn, oyear, omonth, oday);
}
