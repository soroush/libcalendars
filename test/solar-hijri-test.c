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

#include "../src/solar-hijri.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    uint32_t jdn = 0;
    sh_to_jdn(&jdn, 1392, 04, 15);
    printf("Julian Day for 1392/04/15 AP is: %d\n", jdn);
    if(sh_is_leap(1395))
        printf("Yep\n");
//    int fd;
//    int16_t year;
//    uint8_t month;
//    uint16_t day;
//    ssize_t write_size;
//    char buffer[1024];
//    fd = open("data.dat", O_CREAT | O_TRUNC | O_WRONLY,
//              S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//    if(fd < 0)
//    {
//        perror("Unable to open file!");
//        return 77;
//    }
//    for(uint64_t jdn = 0; jdn < 2488434; jdn++) {
//        jdn_to_sh(jdn, &year, &month, &day);
//        sprintf(buffer, "%07ld %+05d %02d %03d\n", jdn, year, month, day);
//        write_size = write(fd, buffer, strlen(buffer));
//        if(write_size < 0) {
//            perror("Unable to write to file!");
//        }
//    }
//    close(fd);
    return 0;
}
