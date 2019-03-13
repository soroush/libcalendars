cmake_minimum_required(VERSION 2.6)
project(calendar_test)

include_directories(../../../src /opt/android-ndk-r10d/platforms/android-3/arch-arm/usr/include/)
add_executable(calendar_test ../jni.c ../../../src/cl-calendars.c  
        ../../../src/cl-gregorian.c  
        ../../../src/cl-islamic-civil.c  
        ../../../src/cl-jewish.c  
        ../../../src/cl-julian.c  
        ../../../src/cl-math.c  
        ../../../src/cl-milankovic.c  
        ../../../src/cl-solar-hijri.c )

install(TARGETS calendar_test RUNTIME DESTINATION bin)
