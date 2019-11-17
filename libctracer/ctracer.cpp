#include <stdio.h>
#include "hook/xHook/xhook.h"
#include "leakcheck/leakcheck_memory.h"
#include "common/virtual_heap.h"

void init_memory_check(const char* pathname){
    for (int i = 0; libc_alloc_funcs[i].symbol_name != nullptr; i++){
        xhook_register(pathname, libc_alloc_funcs[i].symbol_name, libc_alloc_funcs[i].hook_handle, &libc_alloc_funcs[i].old_handle);
    }
}

void ctracer_init(){
    xhook_enable_debug(1);
    // xhook_register("tracerTest", libc_alloc_funcs[0].symbol_name, libc_alloc_funcs[0].hook_handle, NULL);
    // xhook_register("tracerTest", libc_alloc_funcs[3].symbol_name, libc_alloc_funcs[3].hook_handle, NULL);
    init_memory_check("tracerTest");
    printf("start xhook_refresh\n");
    xhook_refresh(0);
}

void ctracer_scan_mem(){
    VirtualHeap::GetInstance()->ScanMem();
}