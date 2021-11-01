//
// Created by hc l on 2021/10/30.
//

#include "include/exception-util.h"

/**
 * 异常抛出工具类
 * @param env
 * @param name
 * @param msg
 */
void JUN_ThrowByName(JNIEnv *env, const char *name, const char *msg) {
    jclass cls = (*env)->FindClass(env, name);
    if (cls == NULL) {
        return;
    }
    (*env)->ThrowNew(env, cls, msg);
    (*env)->DeleteLocalRef(env, cls);
}


