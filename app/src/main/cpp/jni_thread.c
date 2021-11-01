//
// Created by hc l on 2021/10/31.
//

#include "include/jni_thread.h"

jint MonitorEnter(JNIEnv *env, jobject obj) {
    jint result = (*env)->MonitorEnter(env, obj);
    if (result != JNI_OK) {
        //进入失败，处理错误

    }
    return result;
}

jint MonitorExist(JNIEnv *env, jobject obj) {
    jint result = (*env)->MonitorExit(env, obj);
    if (result != JNI_OK) {
        //退出失败，处理错误

    }
    return result;
}

void MonitorWait(JNIEnv *env, jobject obj, jlong timeout) {
    (*env)->CallVoidMethod(env, obj, MID_Object_wait, timeout);
}

void MonitorNotify(JNIEnv *env, jobject obj) {
    (*env)->CallVoidMethod(env, obj, MID_Object_notify);
}

void MonitorNotifyAll(JNIEnv *env, jobject obj) {
    (*env)->CallVoidMethod(env, obj, MID_Object_notifyAll);
}
