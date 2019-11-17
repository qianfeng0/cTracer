#ifndef _HOOK_FUNC_H_
#define _HOOK_FUNC_H_

struct HookFunc
{
    const char* symbol_name;
    void* hook_handle;
    void* old_handle;
};

#endif