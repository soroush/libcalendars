# A calendar implementation library

`libcalendar` is an experimental C library to provide arithmentic for several
calendars including Gregorian and Hijri Shamsi calendars.

## Why?

Why implement yet another calendaring library? Well, there are plenty of
excellent implementations out there, though it seems there is no free,
GPL-compliant, C implementation. Besides there is no precise implementation
of non-gregorian calendars, most importantly Solar Hijri and Islamic Civil
calendars.

## How to use libcalendar?
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
if(sh_s_leap(1395))
    printf("Yep\n");
```

## A note on Solar Hijri...

My implementation of Solar Hijri (Shamsi) calendar is based on median year
calculation obtained from Muousa Akrami's work
:[The development of Iranian calendar: historical and astronomical foundations - 2014](https://arxiv.org/pdf/1111.4926.pdf).
This method is more accurate than 33-year algorithm and supports a wider range
of dates, both in Solar Hijri <-> Gregorian comversions, and in JDN
calculations.
