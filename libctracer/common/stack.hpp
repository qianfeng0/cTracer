#ifndef _STACK_H_
#define _STACK_H_

#include <dlfcn.h>

#include "common_log.h"
#include "common_def.h"

// struct StackWrap{
//     size_t cur;
//     size_t max;
//     void** stack_trace;

//     StackWrap(void** stack, size_t size):cur(0),max(size),stack_trace(stack){};

// };

// void print_stack_wrap(StackWrap* stack_wrap)
// {
//     for(int i = 0; i < stack_wrap->cur; i++){
//         Dl_info info;
//         if (dladdr(stack_wrap->stack_trace[i], &info))
//             LOGD("pc:%p, lib:%s\n", (void*)((char*)stack_wrap->stack_trace[i] - (char*)info.dli_fbase), info.dli_fname);
//         else
//             LOGD("abs pc:%p\n", (char*)stack_wrap->stack_trace[i]);
//     }
// }

class StackBase{
public:
    virtual int save(void* pc) = 0;
    virtual bool isEnd() = 0;
    virtual void clear() = 0;
    // virtual void print() = 0;
};


template<int maxsize>
class StackTrace : public StackBase
{
public:
    StackTrace(/* args */);
    ~StackTrace();

    virtual int save(void* pc);
    virtual bool isEnd();
    virtual void clear();
    void print();
public:
    void* address[maxsize];
    int cur;
};

template<int maxsize>
StackTrace<maxsize>::StackTrace():
cur(0)
{

}

template<int maxsize>
StackTrace<maxsize>::~StackTrace()
{
}

template<int maxsize>
int StackTrace<maxsize>::save(void* pc){
    if (cur >= ARRAY_SIZE(address)){
        return -1;
    }
    address[cur++] = pc;
    return 0;
}

template<int maxsize>
bool StackTrace<maxsize>::isEnd(){
    return cur >= ARRAY_SIZE(address);
}

template<int maxsize>
void StackTrace<maxsize>::clear(){
    cur = 0;
}

template<int maxsize>
void StackTrace<maxsize>::print(){
    for(int i = 0; i < cur; i++){
        Dl_info info;
        if (dladdr(address[i], &info))
            LOGD("pc:%p, lib:%s\n", (void*)((char*)address[i] - (char*)info.dli_fbase), info.dli_fname);
        else
            LOGD("abs pc:%p\n", (char*)address[i]);
    }
}

#endif