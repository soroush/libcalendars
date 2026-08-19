# A calendar implementation library

![language](https://img.shields.io/badge/language-c-blue.svg)
![c](https://img.shields.io/badge/std-c99-blue.svg)
![GCC](https://img.shields.io/badge/GCC-13.0-blue.svg)
![MSVC](https://img.shields.io/badge/MSVC-14-blue.svg)
![license](https://img.shields.io/badge/license-GPLv3-blue.svg)
[![CI](https://github.com/soroush/libcalendars/actions/workflows/ci.yml/badge.svg?branch=dev)](https://github.com/soroush/libcalendars/actions/workflows/ci.yml)

A precise C library to provide arithmentic for the most common calendar 
systems. Currently Gregorian, Julian, Milankovic, Solar Hijri (also known as 
Shamsi or Jalali), Islamic Civilm Jewish (also know as Hebrew), Egyptian and
Babylonian calendar systems are provided.

## Contents
- [Installation](#installation)
- [API Design Philosophy](#api-design-philosophy)
- [Usage](#usage)
    - [Documentation](#documentation)
    - [Contribution](#contribution)
    - [Algorithms](#algorithms)
- [Calendars](#calendars)
    - [Gregorian](#gregorian)
    - [Julian](#julian)
    - [Milanković](#milanković)
    - [Solar Hijri (Jalali, or Shamsi)](#solar-hijri)
    - [Islamic Civil](#islamic-civil)
    - [Egyptian](#egyptian)
    - [Babylonian](#babylonian)
- [License](#license)
    - [Commercial Use Exception](#commercial-use-exception)

## Installation

The easiest way to install `libcalendars` is to use PPA:

```bash
sudo add-apt-repository ppa:soroush-r/solap
sudo apt update
sudo apt install libcalendars1    # installs the library
sudo apt install libcalendars-dev # Installs development headers
```

Alternatively you can compile the package from source:
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
sudo cmake --install . --config Release
```

In case you also want to build and run unit tests:
```bash
cmake -DBUILD_TESTING=ON ..
cmake --build . --config Release
ctest . --config Release
```

If nothing goes wrong, you should see all test passed:
```
    Start 1: Gregorian
1/8 Test #1: Gregorian ........................   Passed    0.68 sec
    Start 2: Julian
2/8 Test #2: Julian ...........................   Passed    0.590 sec
    Start 3: Milankovic
3/8 Test #3: Milankovic .......................   Passed    1.23 sec
    Start 4: SolarHijri
4/8 Test #4: SolarHijri .......................   Passed    1.32 sec
    Start 5: Jewish
5/8 Test #5: Jewish ...........................   Passed   16.35 sec
    Start 6: IslamicCivil
6/8 Test #6: IslamicCivil .....................   Passed    0.94 sec
    Start 7: Egyptian
7/8 Test #7: Egyptian .........................   Passed    0.84 sec
    Start 8: Babylonian
8/8 Test #8: Babylonian .......................   Passed    1.13 sec

100% tests passed, 0 tests failed out of 8
```

## API Design Philosophy

This library is API-less by design. This means the library is not intended to be
used directly as a standalone API. Instead, it only provides arithmetic
implementations meant to be integrated into existing date-time APIs or utilized
by developers when creating their own APIs for handling date-time
operations.

Key Principles:

* No Custom Data Structures: The library
deliberately avoids introducing structures for representing calendar components
(e.g., `year`, `month`, `day`). Instead, it operates exclusively on Plain Data
Types (PDTs), such as integers or other native types, ensuring simplicity and
compatibility with diverse applications.

* Flexibility: By focusing solely on
the arithmetic logic, the library provides a robust foundation for building or
extending higher-level APIs. This design empowers developers to adapt the
library seamlessly to their specific domain requirements without being
constrained by predefined abstractions.

* Integration-Ready: The library
complements existing date-time APIs by adding precise calendar arithmetic
capabilities without altering their design philosophy. It can also be used to
prototype and implement custom solutions efficiently.

## Usage

Almost all algorithms in libcalendar are implemented using Julian Day
calculations. You can convert any date on supported calendars to JDN and vice
versa. For example:

```c
uint32_t jdn = 0;
sh_to_jdn(&jdn, 1392, 04, 15);
printf("Julian Day for 1392/04/15 AP is: %l\n", jdn);
```
Which prints:

```$ Julian Day for 1392/04/15 AP is: 2456480```

You can also use non-jdn broken-down date API. For example you
can check if a year in Solar Hijri calendar is leap or not:

```c
if(sh_is_leap(1395)) /* returns 0 for regular years and 1 for leap years */
    printf("Yep\n");
```
You can also convert calendar dates to/from Gregorian calendar:
```c
int16_t y;
uint8_t m;
uint16_t d;
sh_to_gr(1396, 06, 20, &y, &m, &d);
printf("1396/06/20 AP is %04d-%02d-%02d\n", y, m, d);
gr_to_sh(2017, 09, 11, &y, &m, &d); 
printf("2017-09-11 is %04d-%02d-%02d AP\n", y, m, d);
```
which will print:

```
1396/06/20 AP is 2017-09-11
2017-09-11 is 1396/06/18 AP 
```

## Documentation

Reference of API is available at 
[https://soroush.github.io/libcalendars](https://soroush.github.io/libcalendars/).

## Contribution

This library is written in the hope that it will be useful. With your help, 
`libcalendars` can be better (: You can help `libcalendars` in several ways:

1. Build the library and thest its output. You can [raise an 
issue](https://github.com/soroush/libcalendars/issues) if you've found any 
problem. 

2. Contribute to improve code quality, fix bugs and add new features. Please 
read our [Code of Conduct](CODE_OF_CONDUCT.md) for more details. 

## Algorithms

This library is implemented in C programming language, using no external
dependecies. The C standard library used in libcalendar is C11. Though it should
be possible to compile this library with a C99 compiler.

Most of the conversion algorithms for JDN to calendar and vice versa are
implemented based
[Dr Louis Strous](http://orcid.org/0000-0003-2110-7248)'s work (available online
on [Astronomy](http://aa.quae.nl/en/reken/juliaansedag.html) page). Namely
Gregorian, Julian, Milankovic and Islamic Civil calendars and their JDN
calculations are adopted from above page. Solar Hijri (Shamsi) and Jalali
calendar calculations are implemented based on
[Dr. Mousa Akrami](http://m-akrami.teacher.srbiau.ac.ir/)'s work on median year
length for Persian calendar. (See notes on Solar Hijri calendar).

## Calendars

Following is a list of supported calendars, and a short description (mostly from
wikipedia) about them.

### Gregorian

The Gregorian calendar is internationally the most widely used civil calendar.
It is named after Pope Gregory XIII, who introduced it in October 1582.

The calendar was a refinement to the Julian calendar[3] involving a 0.002%
correction in the length of the year. The motivation for the reform was to stop
the drift of the calendar with respect to the equinoxes and
solstices—particularly the northern vernal equinox, which helps set the date
for Easter. Transition to the Gregorian calendar would restore the holiday to
the time of the year in which it was celebrated when introduced by the early
Church. The reform was adopted initially by the Catholic countries of Europe.
Protestants and Eastern Orthodox countries continued to use the traditional
Julian calendar and adopted the Gregorian reform after a time, at least for
civil purposes and for the sake of convenience in international trade. The last
European country to adopt the reform was Greece, in 1923. Many (but not all)
countries that have traditionally used the Islamic and other religious calendars
have come to adopt this calendar for civil purposes.

### Julian

The Julian calendar, proposed by Julius Caesar in 46 BC (708 AUC), was a reform
of the Roman calendar. It took effect on 1 January 45 BC (AUC 709), by edict.
It was the predominant calendar in the Roman world, most of Europe, and in
European settlements in the Americas and elsewhere, until it was refined and
gradually replaced by the Gregorian calendar, promulgated in 1582 by Pope
Gregory XIII. The Julian calendar gains against the mean tropical year at the
rate of one day in 128 years. For the Gregorian the figure is one day in 3,030
years. The difference in the average length of the year between Julian (365.25
days) and Gregorian (365.2425 days) is 0.002%.

### Milanković

The Revised Julian calendar, also known as the Milanković calendar, or, less
formally, new calendar, is a calendar, developed and proposed by the Serbian
scientist Milutin Milanković in 1923, which effectively discontinued the 340
years of divergence between the naming of dates sanctioned by those Eastern
Orthodox churches adopting it and the Gregorian calendar that has come to
predominate worldwide. This calendar was intended to replace the ecclesiastical
calendar based on the Julian calendar hitherto in use by all of the Eastern
Orthodox Church. The Revised Julian calendar temporarily aligned its dates with
the Gregorian calendar proclaimed in 1582 by Pope Gregory XIII for adoption by
the Christian world. The calendar has been adopted by the Orthodox churches of
Constantinople, Albania, Alexandria, Antioch, Bulgaria, Cyprus, Greece, Poland,
and Romania.

### Solar Hijri

The Solar Hijri calendar, also called the Solar Hejri calendar or Shamsi Hijri
calendar, and abbreviated as SH, is the official calendar of Iran and
Afghanistan. It begins on the vernal equinox (Nowruz) as determined by
astronomical calculation for the Iran Standard Time meridian
(52.5°E or GMT+3.5h). This determination of starting moment is more accurate
than the Gregorian calendar for predicting the date of the vernal equinox,
because it uses astronomical observations rather than mathematical rules.

Each of the twelve months corresponds with a zodiac sign.
The first six months have 31 days, the next five have 30 days, and the last
month has 29 days in usual years but 30 days in leap years. The New Year's Day
always falls on the March equinox.

#### A note on Solar Hijri

My implementation of Solar Hijri (Shamsi) calendar is based on median year
calculation obtained from Muousa Akrami's work:
[The development of Iranian calendar: historical and astronomical foundations - 
2014](https://arxiv.org/pdf/1111.4926.pdf).
This method is more accurate than 33-year algorithm and supports a wider range
of dates, both in Solar Hijri <-> Gregorian comversions, and in JDN
calculations.

### Islamic Civil

The Islamic, Muslim, or Hijri calendar is a lunar calendar consisting of 12 
months in a year of 354 or 355 days. It is used (often alongside the Gregorian 
calendar) to date events in many Muslim countries. It is also used by Muslims to 
determine the proper days of Islamic holidays and rituals, such as the annual 
period of fasting and the proper time for the pilgrimage to Mecca.

The Islamic calendar employs the Hijri era whose epoch was retrospectively 
established as the Islamic New Year of AD 622. During that year, Muhammad and 
his followers migrated from Mecca to Yathrib (now Medina) and established the 
first Muslim community (ummah), an event commemorated as the Hijra. In the West, 
dates in this era are usually denoted AH (Latin: Anno Hegirae, "in the year of 
the Hijra") in parallel with the Christian (AD) and Jewish eras (AM). In Muslim 
countries, it is also sometimes denoted as H from its Arabic form. In English, 
years prior to the Hijra are reckoned as BH ("Before the Hijra").

### Egyptian

The Egyptian calendar is one of the earliest known timekeeping systems,
developed in ancient Egypt to align with the Nile's annual flood cycles. It
played a vital role in organizing agricultural activities and religious
festivals. This calendar is notable for its remarkable simplicity and its
influence on later timekeeping systems, including the Julian and Gregorian
calendars.

The Egyptian calendar was based on a solar year divided into three
seasons of four months each, reflecting the natural cycles of the Nile:

* Akhet (Inundation): The flood season, when the Nile overflowed, 
  replenishing the
  soil.
* Peret (Emergence): The growing season, when crops were planted and 
  cultivated.
* Shemu (Harvest): The dry season, when crops were harvested.

Each of the twelve months contained 30 days, making up a total of 360 days in
the year. To reconcile this structure with the solar year of approximately
365.25 days, the Egyptians added five additional days, known as the "epagomenal
days," at the end of the year. These days were considered outside the normal
calendar and were dedicated to the birthdays of key deities, including Osiris,
Isis, and Horus.

The calendar was not leap-adjusted, meaning it gradually drifted out
of sync with the solar year over centuries. However, its consistency made it
highly practical for everyday use and administrative tasks. This robust
simplicity, combined with its cultural significance, helped the Egyptian
calendar endure for millennia and leave a lasting legacy on the history of
timekeeping.

### Babylonian

The Babylonian calendar, developed in ancient Mesopotamia, is one of the
earliest recorded lunar calendars. It played a crucial role in the
administrative, agricultural, and religious life of the Babylonians. Rooted in
astronomical observations, this calendar reflects the sophisticated
understanding of celestial movements by Babylonian scholars.

The calendar was a lunisolar system, aligning months with the lunar cycle and
years with the solar cycle. It relied on the Metonic Cycle, which states that
235 synodical months are equal to 19 tropical years. These 19 years alternated
between 12 and 13 months, with long years (13 months) occurring in the 1st,
4th, 7th, 9th, 12th, 15th, and 18th years of the cycle. This structure included
125 months of 30 days and 110 months of 29 days, adding up to 6,940 days in
total. In most long years, the 12th month was doubled, but in the 18th year,
the 6th month was doubled instead. Day 1 of month 1 (Nisannu) of year 1 in the
Era of Seleukos corresponded to 3 April 310 BCE in the Julian Calendar (CJDN
1607558).

The Babylonians determined the beginning of each month by observing the phases
of the moon. Since the calendar was partly based on direct observations, the
length of months and years was not entirely fixed. Factors such as weather
conditions could delay the official start of a month if the moon was obscured
by clouds. This variability meant the distribution of months into years
operated independently from the distribution of days into months.

To reconstruct the Babylonian calendar predictably, we can use a mathematically
derived version that closely approximates the historical system. Such a version
would differ from the original calendar by at most one day, capturing its
structure while avoiding the unpredictability of direct lunar observations.

## License

This project is licensed under the **GNU General Public License v3.0 (GPL-3.0)**.  
This means that you are free to use, modify, and distribute the software under the terms of the GPL-3.0 license.

### Commercial Use Exception
While this project is licensed under GPL-3.0, **commercial use is permitted only with prior written permission**.  
However, this permission is **granted free of charge**. The requirement is in place to ensure that commercial usage aligns with the project's goals and values.  

If you wish to use this project in a commercial product or service, please contact us to obtain the necessary permissions.

For details about the GPL-3.0 license, see the [official license text](https://www.gnu.org/licenses/gpl-3.0.html).
