/*
* Copyright 2017 - Soroush Rabiei, <soroush@ametisco.ir>
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

#ifdef _WIN32

#include <stdlib.h>
#include <stdio.h>
#include "tst-windows.h"

#define CALENDAR_COUNT 6

int main(int argc, char *argv[])
{
    DWORD ids[CALENDAR_COUNT], results[CALENDAR_COUNT];
    HANDLE handles[CALENDAR_COUNT];
    size_t index = 0;
    size_t i = 0;
    handles[index] = CreateThread(0, 0, tst_gregorian,      NULL, 0, &ids[index]);
    ++index;
    handles[index] = CreateThread(0, 0, tst_islamic_civil,  NULL, 0, &ids[index]);
    ++index;
    handles[index] = CreateThread(0, 0, tst_jewish,         NULL, 0, &ids[index]);
    ++index;
    handles[index] = CreateThread(0, 0, tst_julian,         NULL, 0, &ids[index]);
    ++index;
    handles[index] = CreateThread(0, 0, tst_milankovic,     NULL, 0, &ids[index]);
    ++index;
    handles[index] = CreateThread(0, 0, tst_solar_hijri,    NULL, 0, &ids[index]);

    for (i = 0; i < CALENDAR_COUNT; ++i)
        results[i] = WaitForSingleObject(handles[i], INFINITE);
    /* Collect test results */
    for (i = 0; i < CALENDAR_COUNT; ++i) {
        if (results[i] == WAIT_OBJECT_0) {
            // the thread handle is signaled - the thread has terminated
            DWORD exitcode;
            BOOL rc = GetExitCodeThread(handles[i], &exitcode);
            if (!rc) {
                printf("Unable to get thread status for %zu!\n", i);
                return -1;
            }
            if (exitcode != 0) {
                printf("Thread exited with status code %u!\n", exitcode);
                return exitcode;
            }
        }
        else {
            printf("Thread is still alive!");
        }
    }
    return 0;
}

#endif /* _WIN32 */
