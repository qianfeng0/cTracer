#ifndef _COMMON_DEF_H_
#define _COMMON_DEF_H_

#define ARRAY_SIZE(a)   (sizeof(a) / sizeof(*(a)))

typedef enum
{
    E_OK = 0,

    E_UNKNOWN = 1000,
    E_NOMEM = 1001,
    E_INVAL = 1002,
    E_BADPARMA = 1003
} ErrorCode;

#endif