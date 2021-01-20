# A calendar implementation library

![language](https://img.shields.io/badge/language-c-blue.svg)
![c](https://img.shields.io/badge/std-c99-blue.svg)
![GCC](https://img.shields.io/badge/GCC-5.4.0-blue.svg)
![GCC](https://img.shields.io/badge/GCC-4.9.3-blue.svg)
![GCC](https://img.shields.io/badge/GCC-4.8.5-blue.svg)
![MSVC](https://img.shields.io/badge/MSVC-14-red.svg)
![license](https://img.shields.io/badge/license-GPLv3-blue.svg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6d907409c4244a0cb1a5e67299672d57)](https://www.codacy.com/app/soroush/libcalendars?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=soroush/libcalendars&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.org/soroush/libcalendars.svg?branch=dev)](https://travis-ci.org/soroush/libcalendars)
[![Build status](https://ci.appveyor.com/api/projects/status/kroimbg1ous41iak?svg=true)](https://ci.appveyor.com/project/soroush/libcalendars)

A precise C library to provide arithmentic for the most common calendar 
systems. Currently Gregorian, Julian, Milankovic, Solar Hijri (also known as 
Shamsi or Jalali), Islamic Civil and Jewish (also know as Hebrew) calendar 
systems are provided.

### Installation

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
1/6 Test #1: Gregorian ........................   Passed    0.31 sec
    Start 2: Julian
2/6 Test #2: Julian ...........................   Passed    0.59 sec
    Start 3: Milankovic
3/6 Test #3: Milankovic .......................   Passed    0.78 sec
    Start 4: SolarHijri
4/6 Test #4: SolarHijri .......................   Passed    0.89 sec
    Start 5: Jewish
5/6 Test #5: Jewish ...........................   Passed   17.46 sec
    Start 6: IslamicCivil
6/6 Test #6: IslamicCivil .....................   Passed    0.53 sec

100% tests passed, 0 tests failed out of 6
```

### Usage

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

### Documentation

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

# Algorithms

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

# Calendars

Following is a list of supported calendars, and a short description (mostly from
wikipedia) about them.

## Gregorian

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

## Julian

The Julian calendar, proposed by Julius Caesar in 46 BC (708 AUC), was a reform
of the Roman calendar. It took effect on 1 January 45 BC (AUC 709), by edict.
It was the predominant calendar in the Roman world, most of Europe, and in
European settlements in the Americas and elsewhere, until it was refined and
gradually replaced by the Gregorian calendar, promulgated in 1582 by Pope
Gregory XIII. The Julian calendar gains against the mean tropical year at the
rate of one day in 128 years. For the Gregorian the figure is one day in 3,030
years. The difference in the average length of the year between Julian (365.25
days) and Gregorian (365.2425 days) is 0.002%.

## Milanković

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

## Solar Hijri

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

### A note on Solar Hijri...

My implementation of Solar Hijri (Shamsi) calendar is based on median year
calculation obtained from Muousa Akrami's work:
[The development of Iranian calendar: historical and astronomical foundations - 
2014](https://arxiv.org/pdf/1111.4926.pdf).
This method is more accurate than 33-year algorithm and supports a wider range
of dates, both in Solar Hijri <-> Gregorian comversions, and in JDN
calculations.

## Islamic Civil

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

