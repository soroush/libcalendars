#ifndef JNI_H
#define JNI_H

#include <jni.h>

#define JAVA_METHOD(name) Java_ir_tooska_Calendar_ ## name

JNIEXPORT void JNICALL JAVA_METHOD(from)
(JNIEnv *env, jobject thisObj, jint type, jint jd);

#endif // JNI_H
