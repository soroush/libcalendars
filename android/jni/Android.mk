LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := calendars
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../src
        
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl

LOCAL_SRC_FILES := \
	cl-jni.c \
        ../../src/cl-calendars.c  \
        ../../src/cl-gregorian.c  \
        ../../src/cl-islamic-civil.c  \
        ../../src/cl-jewish.c  \
        ../../src/cl-julian.c  \
        ../../src/cl-math.c  \
        ../../src/cl-milankovic.c  \
        ../../src/cl-solar-hijri.c 


include $(BUILD_SHARED_LIBRARY)

