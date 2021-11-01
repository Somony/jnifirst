//
// Created by hc l on 2021/10/28.
//

#ifndef JNIFIRST_LOG_H
#define JNIFIRST_LOG_H

#include <android/log.h>

#define LOG_TAG "jnifirst"
#define LOGV(format, ...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, format,##__VA_ARGS__)
#define LOGD(format, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, format,##__VA_ARGS__)
#define LOGW(format, ...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, format,##__VA_ARGS__)
#define LOGI(format, ...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, format,##__VA_ARGS__)
#define LOGE(format, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, format,##__VA_ARGS__)


#endif //JNIFIRST_LOG_H
