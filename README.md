# libcalendars

![language](https://img.shields.io/badge/language-c-blue.svg)
![license](https://img.shields.io/badge/license-GPLv3-blue.svg)
[![CI](https://github.com/soroush/libcalendars/actions/workflows/ci.yml/badge.svg?branch=dev)](https://github.com/soroush/libcalendars/actions/workflows/ci.yml)

A small C library that does the arithmetic for common calendar systems. It
supports the Gregorian, Julian, Milanković (Revised Julian), Solar Hijri
(Shamsi or Jalali), Islamic Civil, Jewish (Hebrew), Egyptian, and Babylonian
calendars.

## Contents

- [Installation](#installation)
- [Design](#design)
- [Usage](#usage)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [Algorithms](#algorithms)
- [Calendars](#calendars)
    - [Gregorian](#gregorian)
    - [Julian](#julian)
    - [Milanković](#milanković)
    - [Solar Hijri](#solar-hijri)
    - [Islamic Civil](#islamic-civil)
    - [Jewish](#jewish)
    - [Egyptian](#egyptian)
    - [Babylonian](#babylonian)
- [License](#license)

## Installation

Build and install from source with CMake (3.16 or newer):

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
sudo cmake --install . --config Release
```

This installs a shared library, a static library, the headers under
`include/libcalendars/`, a pkg-config file (`libcalendars.pc`), and a CMake
package config, so you can link with either `pkg-config --libs libcalendars`
or `find_package(libcalendars)`.

The `debian/` and `rpm/` directories hold packaging files. CI builds `.deb`
and `.rpm` packages from them on every push, and the packages are attached to
the workflow run as artifacts.

To build and run the test suite, configure with `BUILD_TESTING=ON` and use a
Debug build. The tests report failures through `assert`, so a Release build
(which defines `NDEBUG`) would make every test pass no matter what:

```bash
cmake -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
ctest . --config Debug
```

If all goes well you will see every test pass:

```
      Start  1: Gregorian
 1/11 Test  #1: Gregorian .........................   Passed    0.61 sec
      Start  2: Julian
 2/11 Test  #2: Julian ............................   Passed    1.02 sec
      Start  3: Milankovic
 3/11 Test  #3: Milankovic ........................   Passed    1.14 sec
      Start  4: SolarHijri
 4/11 Test  #4: SolarHijri ........................   Passed    1.69 sec
      Start  5: SolarHijriLeapGroundTruth
 5/11 Test  #5: SolarHijriLeapGroundTruth .........   Passed    0.02 sec
      Start  6: SolarHijriConversionGroundTruth
 6/11 Test  #6: SolarHijriConversionGroundTruth ...   Passed    0.02 sec
      Start  7: SolarHijriCorrectionSweep
 7/11 Test  #7: SolarHijriCorrectionSweep .........   Passed    0.02 sec
      Start  8: Jewish
 8/11 Test  #8: Jewish ............................   Passed   15.68 sec
      Start  9: IslamicCivil
 9/11 Test  #9: IslamicCivil ......................   Passed    0.87 sec
      Start 10: Egyptian
10/11 Test #10: Egyptian ..........................   Passed    0.78 sec
      Start 11: Babylonian
11/11 Test #11: Babylonian ........................   Passed    1.06 sec

100% tests passed, 0 tests failed out of 11
```

## Design

This library does not try to be a date and time API. It only provides the
arithmetic, and is meant to sit behind an existing date and time API or to
serve as the base for one you write yourself.

- **No custom data types.** There is no struct for a date. Every function
  takes and returns plain integers: `int16_t` for years, `uint8_t` for months,
  `uint16_t` for days, and `uint32_t` for Julian Day Numbers.
- **Arithmetic only.** Because the library stops at the arithmetic, it does
  not force any particular model of dates, times, or time zones on the code
  that uses it.
- **Easy to integrate.** It can add calendar conversions to an API that
  already exists without changing how that API works, and it is small enough
  to use for quick prototypes.

## Usage

Almost every conversion in the library goes through the Julian Day Number
(JDN). Each calendar has a pair of functions to go from a date to a JDN and
back. For example, for the Solar Hijri calendar:

```c
#include <inttypes.h>
#include <stdio.h>
#include <libcalendars/cl-solar-hijri.h>

uint32_t jdn = 0;
sh_to_jdn(&jdn, 1392, 4, 15);
printf("Julian Day for 1392/04/15 AP is: %" PRIu32 "\n", jdn);
```

This prints:

```
Julian Day for 1392/04/15 AP is: 2456480
```

Each calendar also has functions that work on a broken-down date without going
through a JDN. For example, to check whether a Solar Hijri year is a leap year:

```c
if (sh_is_leap(1395)) /* returns 1 for leap years and 0 otherwise */
    printf("1395 is a leap year\n");
```

Every non-Gregorian calendar has direct conversions to and from the Gregorian
calendar:

```c
int16_t y;
uint8_t m;
uint16_t d;
sh_to_gr(1396, 6, 20, &y, &m, &d);
printf("1396/06/20 AP is %04d-%02d-%02d\n", y, m, d);
gr_to_sh(2017, 9, 11, &y, &m, &d);
printf("2017-09-11 is %04d/%02d/%02d AP\n", y, m, d);
```

This prints:

```
1396/06/20 AP is 2017-09-11
2017-09-11 is 1396/06/20 AP
```

Note that month and day arguments are plain integers. Writing them with a
leading zero, such as `09`, is an octal literal in C and will not compile.

Each calendar has its own header and function prefix:

| Calendar      | Header              | Prefix |
|---------------|---------------------|--------|
| Gregorian     | `cl-gregorian.h`    | `gr_`  |
| Julian        | `cl-julian.h`       | `ju_`  |
| Milanković    | `cl-milankovic.h`   | `ml_`  |
| Solar Hijri   | `cl-solar-hijri.h`  | `sh_`  |
| Islamic Civil | `cl-islamic-civil.h`| `is_`  |
| Jewish        | `cl-jewish.h`       | `jw_`  |
| Egyptian      | `cl-egyptian.h`     | `eg_`  |
| Babylonian    | `cl-babylonian.h`   | `ba_`  |

The header `cl-calendars.h` offers a second, generic interface where the
calendar is picked at run time with a `CAL_*` constant, for example
`convert_date(CAL_GREGORIAN, CAL_SOLAR_HIJRI, ...)`. This interface currently
covers the Gregorian, Julian, Milanković, Islamic Civil, Jewish, and Solar
Hijri calendars. The Egyptian and Babylonian calendars are only available
through their own headers.

## Documentation

The API reference is at
[https://soroush.github.io/libcalendars](https://soroush.github.io/libcalendars/).

## Contributing

This library is written in the hope that it will be useful, and it can get
better with your help. There are two main ways to contribute:

1. Build the library and test its output. If you find a problem, please
   [open an issue](https://github.com/soroush/libcalendars/issues).

2. Improve the code, fix bugs, or add new features. Please read the
   [Code of Conduct](CODE_OF_CONDUCT.md) first.

## Algorithms

The library is written in C with no dependencies beyond the C standard
library and the math library (`libm`). The CMake build sets the C standard to
C90 with compiler extensions enabled, and the source uses a few C99 features
(`<stdint.h>`, `inline`, and `//` comments) that GCC, Clang, and MSVC all
accept in that mode. CI builds and tests on Ubuntu and Windows.

Most of the conversions between calendar dates and Julian Day Numbers follow
the work of [Dr. Louis Strous](http://orcid.org/0000-0003-2110-7248), published
on the [Astronomy Answers](http://aa.quae.nl/en/reken/juliaansedag.html) page.
In particular, the Gregorian, Julian, Milanković, and Islamic Civil
calculations come from that page. The Solar Hijri calendar is described in its
own section below.

## Calendars

This section gives a short description of each supported calendar, mostly
drawn from Wikipedia.

### Gregorian

The Gregorian calendar is the most widely used civil calendar in the world. It
is named after Pope Gregory XIII, who introduced it in October 1582.

It refines the Julian calendar by shortening the average year by 0.002%. The
reason for the reform was to stop the calendar from drifting against the
equinoxes and solstices, in particular the northern vernal equinox, which is
used to set the date of Easter. Catholic countries adopted the reform first.
Protestant and Eastern Orthodox countries kept the Julian calendar for a while
and switched later, at least for civil use and for the convenience of
international trade. The last European country to adopt it was Greece, in
1923. Many (but not all) countries that have traditionally used the Islamic or
other religious calendars now use the Gregorian calendar for civil purposes.

### Julian

The Julian calendar, proposed by Julius Caesar in 46 BC (708 AUC), was a
reform of the Roman calendar. It took effect by edict on 1 January 45 BC
(709 AUC). It was the main calendar of the Roman world, most of Europe, and
the European settlements in the Americas and elsewhere until it was replaced,
gradually, by the Gregorian calendar of 1582. The Julian calendar gains one
day on the mean tropical year every 128 years; the Gregorian calendar gains
one day every 3,030 years. The difference between the average Julian year
(365.25 days) and the average Gregorian year (365.2425 days) is 0.002%.

### Milanković

The Revised Julian calendar, also known as the Milanković calendar or simply
the "new calendar," was proposed by the Serbian scientist Milutin Milanković
in 1923. It closed the 340-year gap that had opened between the dates used by
the Eastern Orthodox churches that adopted it and the Gregorian calendar used
by most of the world. It was meant to replace the Julian calendar that the
whole Eastern Orthodox Church had used for its church calendar until then. For
the time being its dates match the Gregorian calendar. It has been adopted by
the Orthodox churches of Constantinople, Albania, Alexandria, Antioch,
Bulgaria, Cyprus, Greece, Poland, and Romania.

### Solar Hijri

The Solar Hijri calendar, also called the Solar Hejri or Shamsi Hijri calendar
and abbreviated SH, is the official calendar of Iran and Afghanistan. The year
begins on the vernal equinox (Nowruz), fixed by astronomical calculation for
the Iran Standard Time meridian (52.5°E, or UTC+3:30). Because it is tied to
the observed equinox rather than to an arithmetic rule, it tracks the vernal
equinox more closely than the Gregorian calendar does.

Each of the twelve months matches a zodiac sign. The first six months have 31
days, the next five have 30 days, and the last month has 29 days in a common
year and 30 days in a leap year. New Year's Day always falls on the March
equinox.

#### How the library computes Solar Hijri dates

The official calendar is set by observation, so no arithmetic rule can
reproduce it exactly. The library uses the 2820-year cycle, which has 683 leap
years per cycle and a mean year of 365.24219858 days. The cycle starts at
475 AP (Julian Day Number 2121446). The reference used for this rule is
[Mousa Akrami, *The development of Iranian calendar: historical and
astronomical foundations* (2014)](https://arxiv.org/pdf/1111.4926.pdf).

On a handful of years the official leap year sits one year away from where the
2820-year rule puts it. The library carries a short table of those years and
applies it on top of the rule, so that its output matches the published
official calendar for the years the table covers. The test suite checks the
result against a table of official leap years in
`tests/solar-hijri/official-leap-years.csv`. The details, and how the table
was derived, are in
[doc/solar-hijri-official-corrections.md](doc/solar-hijri-official-corrections.md).

### Islamic Civil

The Islamic, Muslim, or Hijri calendar is a lunar calendar with 12 months and
a year of 354 or 355 days. It is used, often alongside the Gregorian calendar,
to date events in many Muslim countries, and by Muslims everywhere to find the
right days for religious observances such as the yearly fast and the
pilgrimage to Mecca.

The calendar counts years from the Hijri era, whose epoch was later fixed as
the Islamic New Year of AD 622. In that year Muhammad and his followers moved
from Mecca to Yathrib (now Medina) and founded the first Muslim community, an
event known as the Hijra. In the West, years in this era are usually marked AH
(Latin *Anno Hegirae*, "in the year of the Hijra"), alongside the Christian
(AD) and Jewish (AM) eras. In Muslim countries the Arabic form H is also used.
In English, years before the Hijra are written BH ("Before the Hijra").

The library implements the tabular (civil) version of this calendar, which
uses a fixed arithmetic rule rather than observation of the new moon.

### Jewish

The Jewish or Hebrew calendar is a lunisolar calendar. Months follow the moon
and years follow the sun, so a year has either 12 or 13 months. Leap years,
with the extra month, fall seven times in every 19-year cycle. A common year
has 353, 354, or 355 days and a leap year has 383, 384, or 385 days; the exact
length depends on rules that push Rosh Hashanah away from certain weekdays.
The library exposes these year types through `jw_is_deficient`,
`jw_is_regular`, and `jw_is_complete`.

### Egyptian

The Egyptian calendar is one of the earliest known timekeeping systems. It was
developed in ancient Egypt to follow the yearly flood of the Nile, and it
organized farming and religious festivals. It is notable for its simplicity
and for its influence on later calendars, including the Julian and Gregorian
calendars.

The year was divided into three seasons of four months each, matching the
cycle of the Nile:

- Akhet (Inundation): the flood season, when the Nile overflowed and renewed
  the soil.
- Peret (Emergence): the growing season, when crops were planted and tended.
- Shemu (Harvest): the dry season, when crops were gathered.

Each of the twelve months had 30 days, for a total of 360 days. To bring this
closer to the solar year of about 365.25 days, the Egyptians added five extra
days, the "epagomenal days," at the end of the year. These days stood outside
the normal calendar and were devoted to the birthdays of major gods, including
Osiris, Isis, and Horus.

The calendar had no leap years, so it slowly drifted against the solar year
over the centuries. Its regularity, however, made it very practical for
everyday and administrative use. The library treats the five epagomenal days
as a short thirteenth month.

### Babylonian

The Babylonian calendar, developed in ancient Mesopotamia, is one of the
earliest recorded lunar calendars. It was central to the administrative,
agricultural, and religious life of Babylon, and it reflects the careful
astronomical observation of Babylonian scholars.

It was a lunisolar system: months followed the moon and years followed the
sun. It relied on the Metonic cycle, in which 235 lunar months equal 19
tropical years. Within each 19-year cycle, 12 years had 12 months and 7 years
had 13, with the long years falling in the 1st, 4th, 7th, 9th, 12th, 15th, and
18th years of the cycle. In most long years the 12th month was doubled; in the
18th year the 6th month was doubled instead. Day 1 of month 1 (Nisannu) of
year 1 of the Seleucid era fell on 3 April 310 BCE in the Julian calendar
(Julian Day Number 1607558).

The Babylonians started each month by observing the new moon, so month and
year lengths were not entirely fixed. Bad weather could delay the official
start of a month if the moon was hidden by clouds. The library implements a
fixed arithmetic version of the calendar that follows the cycle above and
comes within a day of the historical one.

## License

This project is licensed under the GNU General Public License, version 3 or
(at your option) any later version. You are free to use, modify, and
distribute the software under the terms of that license. See
[COPYING](COPYING) for the full text, or read it online at
[gnu.org](https://www.gnu.org/licenses/gpl-3.0.html).
