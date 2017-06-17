#ifndef _LOG_H
#define _LOG_H
 #include <stdio.h>
 #include <android/log.h>

 #ifndef LOG_TAG
 #define LOG_TAG "NATIVE"
 #endif

 #ifndef android_printLog
 #define android_printLog(pri, tag, fmt...) \
	  __android_log_print(pri, tag, fmt)
 #endif

 #ifndef LOG_PRI
 #define LOG_PRI(pri, tag, ...) \
        android_printLog(pri,tag, __VA_ARGS__)
 #endif

 #ifndef ALOG
 #define ALOG(pri, tag, ...) \
        LOG_PRI(ANDROID_##pri,tag, __VA_ARGS__)
 #endif

 #ifndef ALOGV
 #define ALOGV(...) ((void)ALOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
 #endif

 #ifndef ALOGD
 #define ALOGD(...) ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
 #endif

 #ifndef ALOGI
 #define ALOGI(...) ((void)ALOG(LOG_INFO, LOG_TAG, __VA_ARGS__))
 #endif

 #ifndef ALOGW
 #define ALOGW(...) ((void)ALOG(LOG_WARN, LOG_TAG, __VA_ARGS__))
 #endif

 #ifndef ALOGE
 #define ALOGE(...) ((void)ALOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))
 #endif


#endif

