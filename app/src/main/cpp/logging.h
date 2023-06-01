//
// Created by heqyo on 2023/2/4.
//

#ifndef MODIFYFGO_ALTER_LILY_LOGGING_H
#define MODIFYFGO_ALTER_LILY_LOGGING_H

#include <android/log.h>

#define LOGTAG "MorganHook"
#define LSPOSEDLOGTAG "LSPosed-Bridge"
#define LOGV(...) { \
    __android_log_print(ANDROID_LOG_VERBOSE , LOGTAG, __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_VERBOSE , LSPOSEDLOGTAG, __VA_ARGS__); }
#define LOGD(...) { \
    __android_log_print(ANDROID_LOG_DEBUG , LOGTAG, __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_DEBUG , LSPOSEDLOGTAG, __VA_ARGS__); }
#define LOGI(...) { \
    __android_log_print(ANDROID_LOG_INFO , LOGTAG, __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_INFO , LSPOSEDLOGTAG, __VA_ARGS__); }
#define LOGW(...) { \
    __android_log_print(ANDROID_LOG_WARN , LOGTAG, __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_WARN , LSPOSEDLOGTAG, __VA_ARGS__); }
#define LOGE(...) { \
    __android_log_print(ANDROID_LOG_ERROR , LOGTAG, __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_ERROR , LSPOSEDLOGTAG, __VA_ARGS__); }

#endif //MODIFYFGO_ALTER_LILY_LOGGING_H
