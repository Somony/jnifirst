//
// Created by hc l on 2021/10/31.
//

#ifndef JNIFIRST_JNI_THREAD_H
#define JNIFIRST_JNI_THREAD_H

#include <jni.h>

jint MonitorEnter(JNIEnv *env, jobject obj);

jint MonitorExist(JNIEnv *env, jobject obj);

//线程wait和notify jni没有提供方法，只能自行调用java中的
static jmethodID MID_Object_wait;
static jmethodID MID_Object_notify;
static jmethodID MID_Object_notifyAll;

void MonitorWait(JNIEnv *env, jobject obj, jlong timeout);

void MonitorNotify(JNIEnv *env, jobject obj) ;

void MonitorNotifyAll(JNIEnv *env, jobject obj);

#endif //JNIFIRST_JNI_THREAD_H
