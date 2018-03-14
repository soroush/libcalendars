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

#include "cl-math.h"

/**
 * Division of a whole number \f$y\f$ by another whole number \f$x\f$ 
 * results in a quotient \f$q\f$ and a remainder \f$r\f$. In our calculations,
 * the remainder never should be negative. Then \f$0 ≤ r \lt \left|x\right|\f$
 * As a result:
 * 
 *  \f{eqnarray*}{
 *   q &=& \left\lfloor\frac{y}{x}\right\rfloor
 *   \\ r &=& y \bmod x = y − x\left\lfloor\frac{y}{x}\right\rfloor
 *   \\ y &=& qx + r
 *  \f}
 */
div_t pdiv(int y, int x) {
    div_t rv = div(y, x);
    if(rv.rem < 0) {
        if(x>0) {
            rv.quot -= 1;
            rv.rem += x;
        } else {
            rv.quot += 1;
            rv.rem -= x;
        }
    }
    return rv;
}

/**
 * C implentation of integer division results in truncation toward zero. While 
 * we ofthen need floor, ceil or rounding. This function simulates floor 
 * division in an optimized way. It returns:
 * 
 * \f[
 *   \left\lfloor\frac{a}{b}\right\rfloor
 * \f]
 */
int fdiv(int a, int b) {
    return (a - (a < 0 ? b - 1 : 0)) / b;
}

/**
 * This function returns non-negative remainder from division of 
 * \f$y\f$ by \f$x\f$, i.e. \f$x \bmod y\f$
 * 
 * \f[
 *   x \bmod y=x-y\left\lfloor\frac{x}{y}\right\rfloor
 * \f]
 */
int mod(int x, int y) {
    return x - fdiv(x, y) * y;
}
