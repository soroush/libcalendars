# A calendar implementation library

`libcalendar` is an experimental C library to provide arithmentic for several
calendars.

## Getting Started

Almost all algorithms in libcalendar are implemented using Julian Day
calculations. You can convert any date on supported calendars to JDN and vice
versa. For example:

```c
uint32_t jdn = 0;
sh_to_jdn(&jdn, 1392, 04, 15);
printf("Julian Day for 1392/04/15 AP is: %l\n", jdn);
```
Which prints:

```
$ Julian Day for 1392/04/15 AP is: 2456480
```

You can also use non-jdn broken-down date API. For example you
can check if a year in Solar Hijri calendar is leap or not:

```c
if(sh_s_leap(1395))
    printf("Yep\n");
```

### Prerequisites

This library is imolemented in C programming language, using no external
dependecies. The C standard library used in libcalendar is C11. Though it should
be possible to compile this library with a C99 compiler.


### Installing

1. clone git repository:

   ```
   git clone git@github.com:soroush/libcalendars.git
   ```

   or download release tarball from
[github release page](https://github.com/soroush/libcalendars/releases).

2. Configure for build:

   ```
   ./configure
   ```
3. Build:
   ```
   make
   ```
   Or
   ```
   make -jN # Where N is degree of parallelism
   ```

## Running the tests

Please make sure that the library works by running tests, and report any error:
   ```
   make check
   ```
   
# Algorithms

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
[The development of Iranian calendar: historical and astronomical foundations - 2014](https://arxiv.org/pdf/1111.4926.pdf).
This method is more accurate than 33-year algorithm and supports a wider range
of dates, both in Solar Hijri <-> Gregorian comversions, and in JDN
calculations.
 
# Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of
conduct, and the process for submitting pull requests to us.

# Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available,
see the [tags on this repository](https://github.com/soroush/libcalendars/tags).

# Authors

* **Soroush Rabiei**

# License

This project is licensed under the GPL-v3 License - see the [COPYING](COPYING)
file for details.

# Acknowledgments

* Dr. Louis Strous
* Dr. Mousa Akrami
