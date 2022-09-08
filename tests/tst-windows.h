/*
* Copyright 2021 - Soroush Rabiei, <soroush.rabiei@gmail.com>
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

#ifndef LIBCALENDAR_TEST_WINDOWS_H
#define LIBCALENDAR_TEST_WINDOWS_H

#include <windows.h>

DWORD WINAPI tst_gregorian(LPVOID);
DWORD WINAPI tst_islamic_civil(LPVOID);
DWORD WINAPI tst_jewish(LPVOID);
DWORD WINAPI tst_julian(LPVOID);
DWORD WINAPI tst_milankovic(LPVOID);
DWORD WINAPI tst_solar_hijri(LPVOID);

#endif /* LIBCALENDAR_TEST_WINDOWS_H */