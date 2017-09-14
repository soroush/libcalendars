# Libcalendars

**libcalendars** is an experimental C library to provide arithmentic for several
calendars.

## Motivation

Why implement yet another calendaring library? Well, there are plenty of
excellent implementations out there, though it seems there is no free,
GPL-compliant, C implementation. Besides there is no precise implementation
of non-gregorian calendars, most importantly Solar Hijri and Islamic Civil
calendars.

## API

Almost all algorithms in libcalendar are implemented using Julian Day
calculations. You can convert any date on supported calendars to JDN and vice
versa. For example:

```c
uint32_t jdn = 0;
sh_to_jdn(&jdn, 1392, 04, 15);
printf("Julian Day for 1392/04/15 AP is: %l\n", jdn);
```

Which prints:

```bash
$ Julian Day for 1392/04/15 AP is: 2456480
```

You can also use non-jdn broken-down date API. For example you
can check if a year in Solar Hijri calendar is leap or not:

```c
if(sh_is_leap(1395)) /* returns 0 for regular years and 1 for leap years */
    printf("Yep\n");
printf("Number of days in 1395: %d\n", sh_days_in_year(1395));
```

Conversion algorithms for dates in all calendars to/from Gregorian calendar is 
supported through JDN to date conversions:

```c
int16_t y;
uint8_t m;
uint16_t d;
sh_to_gr(1369, 06, 20, &y, &m, &d);
printf("1369/06/20 AP is %04d-%02d-%02d\n", y, m, d);
gr_to_sh(2017, 09, 11, &y, &m, &d); 
printf("2017-09-11 is %04d-%02d-%02d AP\n", y, m, d);
```
which will print:

```
1369/06/20 AP is 2017-09-11
2017-09-11 is 1369/06/18 AP 
```

### Function Naming

Each calendar is identified by a two character abbriviation, which will be used 
either as a prefix or a postfix to all function names. Normally a supported 
calendar will have following functions, which `cl` is calendar abbreviation.

* `cl_is_leap`
* `cl_days_in_month`
* `cl_days_in_year`
* `cl_month_in_year`
* `cl_is_valid`
* `cl_to_jdn`
* `jdn_to_cl`
* `cl_to_gr`
* `gr_to_cl`

## Supported Calendars

| Calendar Name | Alternative Names | Abbriviation  |
| ------------- | ----------------- | ------------- |
| Gregorian |  | `gr`  |
| Julian |  | `ju`  |
| Milankovic | Revised Julian | `ml`  |
| Jewish | Hebrew | `jw`  |
| Solar Hijri  | Shamsi<br>Persian<br>Iranian  | `sh`  |


