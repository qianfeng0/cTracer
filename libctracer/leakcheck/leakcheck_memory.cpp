#include <malloc.h>
#include <string.h>

#include "common_log.h"
#include "unwind_backtrace.h"
#include "virtual_heap.h"
#include "hook_func.h"

void *hook_malloc(size_t size)
{
    LOGD("%zu bytes memory are allocated by libtest.so\n", size);

    void *malloc_ptr = malloc(size);
    if (malloc_ptr == nullptr)
        return malloc_ptr;

    // void* stack[100];
    // StackWrap stack_warp = StackWrap(stack, ARRAY_SIZE(stack));
    // get_stack(&stack_warp);
    // print_stack(stack, ARRAY_SIZE(stack));

    VirtualHeap::GetInstance()->Register(malloc_ptr, size);
    return malloc_ptr;
}

void *hook_realloc(void *ptr, size_t size)
{
    LOGD("hook_realloc %zu bytes memory are realloc by libtest.so\n", size);
    void * realloc_ptr = realloc(ptr, size);

    if (realloc_ptr != nullptr){
        VirtualHeap::GetInstance()->UnRegister(ptr);
        VirtualHeap::GetInstance()->Register(realloc_ptr, size);
    }else{
        if (size == 0){
            // realloc size is 0 --> free();
            VirtualHeap::GetInstance()->UnRegister(ptr);
        }
    }
    return realloc_ptr;
}

void *hook_calloc(size_t nmemb, size_t size)
{
    LOGD("hook_calloc %zu bytes memory are allocated by libtest.so\n", size);
    void *calloc_ptr = calloc(nmemb, size);
    if (calloc_ptr != nullptr)
        VirtualHeap::GetInstance()->Register(calloc_ptr, nmemb * size);
    return calloc_ptr;
}

void hook_free(void *ptr)
{
    LOGD("hook_free  bytes memory are allocated by libtest.so\n");
    VirtualHeap::GetInstance()->UnRegister(ptr);
    return free(ptr);
}

HookFunc libc_alloc_funcs[]= {
    {"malloc", (void*)hook_malloc, nullptr},
    {"realloc", (void*)hook_realloc, nullptr},
    {"calloc", (void*)hook_calloc, nullptr},
    {"free", (void*)hook_free, nullptr},
    {nullptr, nullptr, nullptr}
};
