//
// Created by hc l on 2021/10/30.
//

#ifndef JNIFIRST_EXCEPTION_UTIL_H
#define JNIFIRST_EXCEPTION_UTIL_H

#include <jni.h>

void JUN_ThrowByName(JNIEnv *env, const char *name, const char *msg);

#endif //JNIFIRST_EXCEPTION_UTIL_H
