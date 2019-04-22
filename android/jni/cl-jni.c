#include "../../src/cl-calendars.h"
#include "cl-jni.h"

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL JAVA_METHOD(from)
(JNIEnv *env, jobject thisObj, jint type, jint jd)
{
    jclass cls = (*env)->GetObjectClass(env, thisObj);
    jfieldID year_id = (*env)->GetFieldID(env, cls, "year", "S");
    jfieldID month_id = (*env)->GetFieldID(env, cls, "month", "S");
    jfieldID day_id = (*env)->GetFieldID(env, cls, "day", "S");

    int16_t year = 0;
    uint8_t month = 0;
    uint16_t day = 0;

    switch (type) {
    case CAL_GREGORIAN:
        jdn_to_gr(jd, &year, &month, &day);
        break;

    case CAL_JULIAN:
        jdn_to_ju(jd, &year, &month, &day);
        break;

    case CAL_MILANKOVIC:
        jdn_to_ml(jd, &year, &month, &day);
        break;

    case CAL_ISLAMIC_CIVIL:
        jdn_to_is(jd, &year, &month, &day);
        break;

    case CAL_JEWSISH:
        jdn_to_ju(jd, &year, &month, &day);
        break;

    case CAL_SOLAR_HIJRI:
        jdn_to_sh(jd, &year, &month, &day);
        break;
    }

    (*env)->SetShortField(env, thisObj, year_id, year);
    (*env)->SetShortField(env, thisObj, month_id, month);
    (*env)->SetShortField(env, thisObj, day_id, day);
}

uint32_t _to_jdn(int16_t year, uint8_t month, uint16_t day, int type) {
    uint32_t jd = 0;

    switch (type) {
    case CAL_GREGORIAN:
        gr_to_jdn(&jd, year, month, day);
        break;

    case CAL_JULIAN:
        ju_to_jdn(&jd, year, month, day);
        break;

    case CAL_MILANKOVIC:
        ml_to_jdn(&jd, year, month, day);
        break;

    case CAL_ISLAMIC_CIVIL:
        is_to_jdn(&jd, year, month, day);
        break;

    case CAL_JEWSISH:
        ju_to_jdn(&jd, year, month, day);
        break;

    case CAL_SOLAR_HIJRI:
        sh_to_jdn(&jd, year, month, day);
        break;
    }

    return jd;
}

#ifdef __cplusplus
}
#endif
