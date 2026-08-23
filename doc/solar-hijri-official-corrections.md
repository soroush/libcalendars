# Reconciling the Solar Hijri calendar with the official calendar of Iran

## The problem

libcalendars implements the Solar Hijri calendar with the arithmetic 2820 year
rule. A year $y$ is a leap year when

$$
\mathrm{frac}\!\left((y + 2346)\,\lambda\right) < \lambda,
\qquad \lambda = \frac{683}{2820} = 0.242198\ldots
$$

and the first day of year $y$ is placed at

$$
N_{\mathrm{arith}}(y) = E + c\,D + \left\lfloor y_c \cdot L \right\rfloor,
$$

where $E = 2121446$ is the Julian day number of 475-01-01 AP, $D = 1029983$ is
the length of a cycle in days, $L = 365.242198\ldots$ is the mean year length,
$c$ is the cycle index and $y_c$ the year's offset within its cycle.

The rule is exact, reversible and self consistent. It is also not the calendar
Iran actually uses. The civil calendar places Nowruz on the day of the vernal
equinox as observed at the reference meridian, and where the equinox falls near
noon the decision is settled by decree rather than by computation. On a small
number of years the decree lands one year away from where the arithmetic rule
puts the leap year, which shows up as a one day disagreement in the conversions
and as an outright disagreement about which years are leap.

This cannot be fixed by choosing a better ratio, epoch or tolerance. The
analysis below establishes that, and the fix that follows treats the
disagreements as what they are: data, not arithmetic.

## The ground truth

The published official table, `tests/solar-hijri/official-leap-years.csv`, is
the reference. Each row gives Nowruz of one Solar Hijri year and the leap flags
assigned to it:

| column | meaning |
| --- | --- |
| `SH_Y`, `SH_M`, `SH_D` | Solar Hijri date, always the first of the first month |
| `L_4` | the year is a leap year four years after the previous one |
| `L_5` | the year is a leap year five years after the previous one |
| `G_Y`, `G_M`, `G_D` | the Gregorian date of the same day |

A year is a leap year when either flag is set. The two are never set together.

The table covers 293 years, 1206 to 1498 AP, mapping to 1827-03-22 through
2119-03-21.

### Validation of the table

An earlier revision of the file was produced by a faulty extraction and carried
six malformed rows. The loader in `tests/solar-hijri/ground-truth.c` rejects
malformed input rather than skipping it, which is how they were found: five rows
carried `SH_D = 0`, and year 1441 carried `L_4 = 1` and `L_5 = 1` at once. The
file was regenerated, and the regenerated file agreed with the repaired one
byte for byte. Both were then checked against the following independent
properties, all of which hold:

- every row parses into eight integers, and `SH_M = SH_D = 1` throughout;
- `SH_Y` runs contiguously from 1206 to 1498 with no gaps or duplicates;
- every Gregorian date is valid, and the dates increase strictly;
- for every consecutive pair of rows,
  $N(y{+}1) - N(y) = 366$ when year $y$ is flagged leap and $365$ otherwise,
  over all 292 intervals;
- `L_5` is set exactly when the gap from the previous leap year is five years,
  and `L_4` exactly when it is four; the gap histogram is
  $\{4 : 62,\ 5 : 8\}$ with no other value;
- `G_M` is always 3, and `G_D` only ever 20, 21 or 22;
- the leap density is $71/293 = 0.242321$, against $683/2820 = 0.242199$.

Spot checks against dates outside the file's own logic agree as well: Nowruz
1391 on 2012-03-20, 1395 on 2016-03-20, 1398 on 2019-03-21, 1399 on 2020-03-20,
1400 on 2021-03-21, 1403 on 2024-03-20, 1404 on 2025-03-21, and the known modern
leap sequence 1370, 1375, 1379, 1383, 1387, 1391, 1395, 1399, 1403, 1408 with
its five year gaps at 1375 and 1408.

The header of the file reads `L_4,L5`; the fifth column is missing its
underscore. The loader skips the header, so nothing depends on it, and the file
is kept as delivered.

## The disagreement

Measured by `tests/solar-hijri/solar-hijri-leap.c` and
`tests/solar-hijri/solar-hijri-conversion.c`, the uncorrected rule disagrees
with the table on ten years:

| year | official | arithmetic |
| --- | --- | --- |
| 1209 | normal | leap |
| 1210 | leap | normal |
| 1242 | normal | leap |
| 1243 | leap | normal |
| 1275 | normal | leap |
| 1276 | leap | normal |
| 1436 | leap | normal |
| 1437 | normal | leap |
| 1469 | leap | normal |
| 1470 | normal | leap |

Both sides count 71 leap years over the range, so the ten disagreements are five
swaps rather than five insertions. Each swap moves a leap year by one step,
which displaces Nowruz for exactly one year and then returns:

| year | official Nowruz | library Nowruz |
| --- | --- | --- |
| 1210 | 1831-03-21 | 1831-03-22 |
| 1243 | 1864-03-20 | 1864-03-21 |
| 1276 | 1897-03-20 | 1897-03-21 |
| 1437 | 2058-03-21 | 2058-03-20 |
| 1470 | 2091-03-21 | 2091-03-20 |

Five wrong dates out of 293, all off by exactly one day, in both conversion
directions.

## Analysis

### There is a harmonic, and it is the 33 year cycle

The disagreements are not scattered. They come 33 years apart: 1209, 1242, 1275
and then 1436, 1469. The reason is visible in the continued fraction expansion
of the leap ratio,

$$
\frac{683}{2820} = [\,0; 4, 7, 1, 3, 5, 4\,],
$$

whose convergents are

$$
\frac{1}{4},\quad \frac{7}{29},\quad \frac{8}{33},\quad \frac{31}{128},\quad
\frac{163}{673},\quad \frac{683}{2820}.
$$

Advancing by a convergent denominator moves the fractional part
$\mathrm{frac}((y + 2346)\lambda)$ by a very small amount:

$$
33\lambda \equiv -0.007447, \qquad
128\lambda \equiv +0.001418, \qquad
2820\lambda \equiv 0 \pmod 1 .
$$

So a year sitting close to the leap decision boundary is followed by another
close year 33 later, drifting toward the boundary by $0.00745$ each time. The
observed run bears this out exactly: the distances from the boundary for 1209,
1242, 1275 are $1.60 \times 10^{-2}$, $8.51 \times 10^{-3}$,
$1.06 \times 10^{-3}$, decreasing by $7.45 \times 10^{-3}$ per step. The 161
year gap between the two runs is $128 + 33$, both convergents.

### The harmonic does not predict the decrees

The tempting conclusion is that the fragile years can be identified from the
rule alone. They cannot. Ranking every year in the table by its distance from
the leap decision boundary,

$$
\delta(y) = \min\Bigl(\mathrm{frac}(\theta),\ \bigl|\lambda -
\mathrm{frac}(\theta)\bigr|,\ 1 - \mathrm{frac}(\theta)\Bigr),
\qquad \theta = (y + 2346)\lambda,
$$

gives:

| rank | years | $\delta$ | decreed differently |
| --- | --- | --- | --- |
| 1 | 1275, 1276 | $1.06 \times 10^{-3}$ | yes |
| 2 | 1403, 1404 | $2.48 \times 10^{-3}$ | no |
| 3 | 1436, 1437 | $4.96 \times 10^{-3}$ | yes |
| 4 | 1308, 1309 | $6.38 \times 10^{-3}$ | no |
| 5 | 1242, 1243 | $8.51 \times 10^{-3}$ | yes |
| 6 | 1370, 1371 | $9.93 \times 10^{-3}$ | no |
| 7 | 1498 | $1.13 \times 10^{-2}$ | no |
| 8 | 1469, 1470 | $1.24 \times 10^{-2}$ | yes |
| 9 | 1341, 1342 | $1.38 \times 10^{-2}$ | no |
| 10 | 1213, 1214 | $1.52 \times 10^{-2}$ | no |
| 11 | 1209, 1210 | $1.60 \times 10^{-2}$ | yes |

The single closest year to the boundary was decreed differently; the second
closest was not. Twenty one years fall inside the band that contains all ten
disagreements, and only ten of them disagree. **No threshold separates the two
groups**, so no refinement of the arithmetic reproduces the official table. The
disagreements are decisions, and the only correct way to represent a decision is
to record it.

For scale, $182$ of every $2820$ years, or $6.5\%$, fall within
$1.6 \times 10^{-2}$ of the boundary. The published range supplies decrees for
five swaps and says nothing about the rest.

### Corrections must be applied in whole swaps

A leap year correction is not a local edit. Making a year longer or shorter
moves every subsequent Nowruz. `tests/solar-hijri/solar-hijri-correction-sweep.c`
measures this directly. It models a correction as a set of pinned years, each
carrying a delta of $+1$ where the officials add a day and $-1$ where they
remove one, and derives both quantities from the same pin set:

$$
\mathrm{leap}^{*}(y) = \mathrm{leap}_{\mathrm{arith}}(y) \oplus \mathrm{pinned}(y),
$$

$$
N^{*}(y) = N_{\mathrm{arith}}(y) + \sum_{\substack{e \in P \\ e < y}} \Delta_e .
$$

The invariant that ties them together is

$$
N^{*}(y + 1) - N^{*}(y) =
\begin{cases}
366 & \mathrm{leap}^{*}(y) \\
365 & \text{otherwise.}
\end{cases}
$$

Applying the disagreements one at a time, in year order:

| pinned | leap wrong | Nowruz wrong | min drift | max drift | invariant violations |
| --- | --- | --- | --- | --- | --- |
| none | 10 | 5 | -1 | +1 | 0 |
| 1209 | 9 | 286 | -2 | 0 | 0 |
| 1210 | 8 | 4 | -1 | +1 | 0 |
| 1242 | 7 | 254 | -2 | 0 | 0 |
| 1243 | 6 | 3 | -1 | +1 | 0 |
| 1275 | 5 | 222 | -2 | 0 | 0 |
| 1276 | 4 | 2 | -1 | 0 | 0 |
| 1436 | 3 | 60 | 0 | +1 | 0 |
| 1437 | 2 | 1 | -1 | 0 | 0 |
| 1469 | 1 | 28 | 0 | +1 | 0 |
| 1470 | 0 | 0 | 0 | 0 | 0 |

Applying them as whole swaps:

| pinned | leap wrong | Nowruz wrong | min drift | max drift | invariant violations |
| --- | --- | --- | --- | --- | --- |
| none | 10 | 5 | -1 | +1 | 0 |
| through 1210 | 8 | 4 | -1 | +1 | 0 |
| through 1243 | 6 | 3 | -1 | +1 | 0 |
| through 1276 | 4 | 2 | -1 | 0 | 0 |
| through 1437 | 2 | 1 | -1 | 0 | 0 |
| through 1470 | 0 | 0 | 0 | 0 | 0 |

Three results follow.

**A half applied swap is silently wrong, not loudly broken.** The invariant
column is zero on every row, including the disastrous ones. Pinning 1209 alone
yields a perfectly self consistent calendar in which 286 of the 293 Nowruz dates
are one day off. Nothing but the ground truth detects it, which is the argument
for keeping the table in the test suite rather than only in the source.

**The swap is the atom of correction.** Because the two years of a swap are
adjacent and their deltas cancel, the running offset returns to zero one year
later, and only the later year of each swap ever starts on a different day from
the arithmetic rule.

**The swaps do not interfere.** Applied as whole swaps the error falls
monotonically, $5 \to 4 \to 3 \to 2 \to 1 \to 0$, with no regression at any
step. Any subset of whole swaps is safe, so the correction set can grow if
further decrees are published.

Because each swap cancels, the running offset is non zero on exactly five
isolated years:

$$
\sum_{e < y} \Delta_e =
\begin{cases}
-1 & y \in \{1210,\ 1243,\ 1276\} \\
+1 & y \in \{1437,\ 1470\} \\
0 & \text{otherwise.}
\end{cases}
$$

## Decisions

### The public interface does not change

`sh_is_leap`, `sh_to_jdn`, `jdn_to_sh`, `sh_to_gr` and `gr_to_sh` keep their
signatures and their names, and now answer for the calendar in civil use in
Iran. A calendar library should report the calendar people actually keep, and a
caller asking whether 1210 was a leap year wants the answer the officials gave.

The uncorrected rule is therefore no longer reachable through the library. The
sweep harness carries its own copy of it, since it exists to measure the gap
between the rule and the decrees and would otherwise report that there is
nothing to measure.

### The corrections live in a table, in the library

`lib/src/cl-solar-hijri.c` carries the five swaps:

```c
static const struct sh_leap_swap_t
{
  int16_t from;
  int16_t to;
} sh_leap_swaps[]
    = { { 1209, 1210 }, { 1242, 1243 }, { 1275, 1276 },
        { 1437, 1436 }, { 1470, 1469 } };
```

`from` is the year the arithmetic rule makes leap, `to` is the year the
officials made leap instead. Two helpers read the table: `sh_leap_correction`
returns $+1$, $-1$ or $0$ for the leap decision, and `sh_nowruz_correction`
returns the running day offset. Neither is exported.

### Both directions go through one corrected year start

The original code computed leap years from `sh_is_leap` and year starts from
`fdoy_c` independently. They agreed only because the arithmetic rule is self
consistent; under correction they would separate. Both now flow through a single
helper:

```c
static int32_t sh_nowruz_jdn (int16_t year);
```

`sh_to_jdn` uses it directly. `jdn_to_sh` estimates the year from the mean year
length as before, then walks the estimate onto the year that actually contains
the day:

```c
while ((int32_t)jd < start)                         { --y; start = sh_nowruz_jdn (y); }
while ((int32_t)jd >= start + sh_days_in_year (y))  { ++y; start = sh_nowruz_jdn (y); }
```

The loops replace the single `if` the original used. The estimate ignores the
decrees, so it can land one year off on either side, and a fixed one step
adjustment is not enough. `sh_days_in_month` and `sh_days_in_year` need no
change; they read `sh_is_leap` and follow automatically.

### The leap test is exact integer arithmetic, not a floating point fraction

Making the leap years and the year starts share one source exposed a defect
that had been sitting under the old code. `sh_is_leap` asked whether

$$
\mathrm{frac}\!\left((y + 2346)\,\lambda\right) < \lambda
$$

with $\lambda$ held as a `double`. The same question, written as an integer
remainder, is

$$
\bigl((y + 2346) \cdot 683\bigr) \bmod 2820 < 683,
$$

and the remainder form is not an optimisation, it is the only form that is
correct. The floating point version fails in two places:

1. **Before year -2346** the product is negative, and so is the fraction
   `modf` hands back. A negative fraction is always below the threshold, so
   every year before -2346 was reported as a leap year. Over the range
   $[-8000, 8000]$ that is 4285 wrong answers.
2. **On the threshold itself** the quotient rounds just under and the year is
   called leap when it is not. This happens at year 475 and at the same
   position in every cycle, for example 3295.

The two forms were compared over $[-8000, 8000]$: they differ on exactly those
4285 negative years plus 475 and 3295, and on nothing else. Neither the
corrected years nor the published range 1206 to 1498 is affected.

The decisive check is against `fdoy_c`, which computes year starts from
$\lfloor y_c \cdot L \rfloor$ and never had the problem, because $y_c$ is
always in $[0, 2820)$. Over a full cycle:

| leap test | years where the year length disagrees with `fdoy_c` |
| --- | --- |
| integer remainder | 0 of 2820 |
| floating point fraction | 1 of 2820 |

That single year is 475, the start of the cycle, and it is the reason
`jdn_to_sh` produced a date discontinuity there. `cl-math.c` already provided
`mod`, which returns a non-negative remainder, so both failures fall out at
once.

### The month walk happens before the year is renumbered

`jdn_to_sh` computed the day of the year against the astronomical year, then
applied the no year zero adjustment `if (y <= 0) { y--; }`, and only then
walked the months. The month lengths were therefore read from the neighbouring
year, whose leap status generally differs, so every year boundary in the
negative range produced a discontinuity such as -5335-12-30 followed by
-5334-01-02. The adjustment now happens after the month walk, which is the last
thing the function does before writing its results.

The rest of the file was already consistent about this. `sh_to_jdn` folds year
zero in first with `if (year < 0) { ++year; }` and works in astronomical
numbering throughout, and `sh_nowruz_jdn` expects the same.

### The public leap functions answer on the historical scale

Everywhere else in the library, a public function takes a year on the
historical scale, the one with no year zero, and shifts it inward.
`gr_is_leap` opens with `if (year < 0) { ++year; }` for exactly this reason,
and `gr_days_in_month` and `gr_days_in_year` inherit the shift by calling it.

`sh_is_leap` never had that shift, so it read its argument as an astronomical
year while `sh_to_jdn`, `jdn_to_sh` and `sh_is_valid` read theirs as
historical. For positive years the two scales coincide and nothing showed. For
negative years they are one apart, so `sh_days_in_year` answered for the
neighbouring year: `jdn_to_sh` would report a year of 366 counted days and
`sh_days_in_year` would call the same year 365.

The rule now exists twice. `sh_is_leap_a`, `sh_days_in_month_a` and
`sh_days_in_year_a` are private and work on the astronomical scale, which is
what the conversions hold internally. The public `sh_is_leap` shifts and
delegates, and `sh_days_in_month` and `sh_days_in_year` inherit the shift
through it, the same arrangement the Gregorian calendar uses.

This is the defect that `test_continuity` catches and a walk over the dates
does not. The dates either side of a negative year boundary are perfectly
consecutive, because `jdn_to_sh` derives them from the year start; it is only
when the counted length of the year is compared against `sh_days_in_year` that
the two scales are seen to disagree.

### Outside 1206 to 1498 the arithmetic rule stands alone

No decree exists outside the published range, so there is nothing to correct
there and no range check is needed. Both helpers return zero for years the table
does not mention, and the arithmetic rule answers unmodified.

### The tests keep the table

Three programs live in `tests/solar-hijri/`:

- `solar-hijri-leap.c` checks every leap decision against the table;
- `solar-hijri-conversion.c` checks `sh_to_gr` and `gr_to_sh` in both
  directions against every row;
- `solar-hijri-correction-sweep.c` reports the incremental measurement above.

The first two were written to fail, and did, with 10 and 5 mismatches. They now
pass and serve as regression tests. The sweep reports rather than asserting, and
ends with a row read straight off the library as built, so a future change to the
correction set that does not match the model is visible immediately. The sweep
carries its own copy of the leap test in the same exact integer form the library
uses, and reproduces the pre correction figures from it, which is what confirms
the copy is faithful.

`test_continuity` is enabled for the Solar Hijri calendar in
`tests/solar-hijri/solar-hijri.c`.

The test suite was also reorganised: each calendar's test moved into its own
directory under `tests/`, with the shared `calendar-arithmetic.c` left at the
root.

## Verification

With `-DBUILD_TESTING=ON`, all eleven tests pass. Relevant results:

- `SolarHijri`: `test_julian_day`, `test_gregorian_calendar` and
  `test_continuity` over $\mathrm{JDN} \in [0,\ 2488069)$, roughly 2.49 million
  round trips in each direction;
- `SolarHijriLeapGroundTruth`: 293 years checked, 0 mismatches, down from 10;
- `SolarHijriConversionGroundTruth`: 293 dates checked, 0 mismatches in each
  direction, down from 5 and 5;
- `SolarHijriCorrectionSweep`: the library as built reports 0 leap errors,
  0 Nowruz errors, 0 drift and 0 invariant violations.

`test_continuity` had been commented out since before this work. It asserts
that consecutive Julian day numbers map to consecutive dates, and that the
counted length of every month and every year matches `sh_days_in_month` and
`sh_days_in_year`. With the three defects above repaired it passes over the
whole range and is now enabled. A standalone walk over the same range counts
zero discontinuities, against 4286 before the repair, and zero disagreements
between counted and reported lengths.

The tests must be built with assertions enabled to mean anything. `assert` is
what `test_julian_day`, `test_gregorian_calendar` and `test_continuity` report
through, and a release build defines `NDEBUG` and compiles all three into
nothing, so they pass without checking. The CI workflow configures with
`-DCMAKE_BUILD_TYPE=Debug` for this reason. The three ground truth programs
report through exit codes instead and are unaffected by the build type.

## Known limitations

**The correction is only as wide as the published table.** Dates before 1206 or
after 1498 AP use the arithmetic rule. That is correct in the sense that no
decree contradicts them, but it is extrapolation, and roughly $6.5\%$ of years
sit close enough to the boundary that a future decree could move them.

**The leap year answer changed for years before -2346 and for year 475.** This
is a repair, not a behaviour change to be preserved: those years were answered
by a floating point fraction that was simply wrong, and the new answers agree
with the year starts the library has always computed. Any caller that recorded
the old answers for those years recorded a bug.
