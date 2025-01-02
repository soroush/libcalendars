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

#include <libcalendars/cl-egyptian.h>
#include <libcalendars/cl-gregorian.h>
#include <check.h>

#include "calendar-arithmetic.h"

#include <stdlib.h>
#include <assert.h>

START_TEST(egyptian_jdn)
{
    uint32_t jd = 0;
    uint32_t out_jd = 0;
    for (jd = 0; jd < 2488069; jd++)
    {
        test_julian_day(&eg_to_jdn, &jdn_to_eg, jd, &out_jd);
        assert(jd == out_jd);
    }
}
END_TEST

START_TEST(egyptian_gregorian)
{
    uint32_t jd = 0;
    uint32_t out_jd = 0;
    uint32_t in_jd;
    int16_t gyi;
    uint8_t gmi;
    uint16_t gdi;
    int16_t gyo;
    uint8_t gmo;
    uint16_t gdo;
    for (jd = 0; jd < 2488069; jd++)
    {
        test_gregorian_calendar(&eg_to_gr, &gr_to_eg, jd,
            &gyi, &gmi, &gdi,
            &gyo, &gmo, &gdo);
        assert(gyi == gyo);
        assert(gmi == gmo);
        assert(gdi == gdo);
    }
}
END_TEST

Suite* create_tests(void)
{
    Suite* suit;
    TCase* egyptian;

    suit = suite_create("Calendar Arithmetic");

    egyptian = tcase_create("Egyptian");
    tcase_add_test(egyptian, egyptian_jdn);
    tcase_add_test(egyptian, egyptian_gregorian);

    suite_add_tcase(suit, egyptian);
    return suit;
}

int main(void)
{
    int number_failed;
    Suite* all_tests;
    SRunner* runner;

    all_tests = create_tests();
    runner = srunner_create(all_tests);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}