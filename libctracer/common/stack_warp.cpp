
#include <dlfcn.h>

#include "common_log.h"
#include "common_def.h"

#include "stack_warp.h"

void print_stack_wrap(StackWrap* stack_wrap)
{
    for(size_t i = 0; i < stack_wrap->cur; i++){
        Dl_info info;
        if (dladdr(stack_wrap->stack_trace[i], &info))
            LOGD("pc:%p, lib:%s\n", (void*)((char*)stack_wrap->stack_trace[i] - (char*)info.dli_fbase), info.dli_fname);
        else
            LOGD("abs pc:%p\n", (char*)stack_wrap->stack_trace[i]);
    }
}

void print_stack(void** stack, size_t size)
{
    for(size_t i = 0; (i < size && stack[i] != nullptr); i++){
        Dl_info info;
        if (dladdr(stack[i], &info))
            LOGD("pc:%p, lib:%s\n", (void*)((char*)stack[i] - (char*)info.dli_fbase), info.dli_fname);
        else
            LOGD("abs pc:%p\n", (char*)stack[i]);
    }
}