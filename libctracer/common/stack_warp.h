
#ifndef _STACK_WARP_H_
#define _STACK_WARP_H_

#include <dlfcn.h>
#include <stddef.h>

struct StackWrap{
    size_t cur;
    size_t max;
    size_t offset;
    void** stack_trace;

    StackWrap(void** stack, size_t size, size_t offs = 0):cur(0),max(size),offset(offs),stack_trace(stack){};
};

void print_stack(void** stack, size_t size);
#endif