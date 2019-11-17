// Copyright (c) 2018-present, iQIYI, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// Created by caikelun on 2018-04-11.

#ifndef XH_LOG_H
#define XH_LOG_H 1

#ifdef __android__
#include <android/log.h>
#else
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __android__
extern android_LogPriority xh_log_priority;
#define XH_LOG_TAG "xhook"
#define XH_LOG_DEBUG(fmt, ...) do{if(xh_log_priority <= ANDROID_LOG_DEBUG) __android_log_print(ANDROID_LOG_DEBUG, XH_LOG_TAG, fmt, ##__VA_ARGS__);}while(0)
#define XH_LOG_INFO(fmt, ...)  do{if(xh_log_priority <= ANDROID_LOG_INFO)  __android_log_print(ANDROID_LOG_INFO,  XH_LOG_TAG, fmt, ##__VA_ARGS__);}while(0)
#define XH_LOG_WARN(fmt, ...)  do{if(xh_log_priority <= ANDROID_LOG_WARN)  __android_log_print(ANDROID_LOG_WARN,  XH_LOG_TAG, fmt, ##__VA_ARGS__);}while(0)
#define XH_LOG_ERROR(fmt, ...) do{if(xh_log_priority <= ANDROID_LOG_ERROR) __android_log_print(ANDROID_LOG_ERROR, XH_LOG_TAG, fmt, ##__VA_ARGS__);}while(0)
#else

typedef enum android_LogPriority {
 ANDROID_LOG_UNKNOWN = 0,
 ANDROID_LOG_DEFAULT, /* only for SetMinPriority() */
 ANDROID_LOG_VERBOSE,
 ANDROID_LOG_DEBUG,
 ANDROID_LOG_INFO,
 ANDROID_LOG_WARN,
 ANDROID_LOG_ERROR,
 ANDROID_LOG_FATAL,
 ANDROID_LOG_SILENT, /* only for SetMinPriority(); must be last */
} android_LogPriority;

extern android_LogPriority xh_log_priority;
#define XH_LOG_DEBUG(fmt, ...) do{if(xh_log_priority <= ANDROID_LOG_DEBUG) printf(fmt"\n", ##__VA_ARGS__);}while(0)
#define XH_LOG_INFO(fmt, ...)  do{if(xh_log_priority <= ANDROID_LOG_INFO)  printf(fmt"\n", ##__VA_ARGS__);}while(0)
#define XH_LOG_WARN(fmt, ...)  do{if(xh_log_priority <= ANDROID_LOG_WARN)  printf(fmt"\n", ##__VA_ARGS__);}while(0)
#define XH_LOG_ERROR(fmt, ...) do{if(xh_log_priority <= ANDROID_LOG_ERROR) printf(fmt"\n", ##__VA_ARGS__);}while(0)
#endif

#ifdef __cplusplus
}
#endif

#endif
