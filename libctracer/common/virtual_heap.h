#ifndef _VIRTUAL_HEAP_H_
#define _VIRTUAL_HEAP_H_

#include <stdint.h>
#include <stddef.h>
#include <mutex>
#include <unordered_map>

#include "stack.hpp"

#define ALLOC_STACK_DEPTH   (5)

struct AllocInfo{
    void* alloc_ptr;
    size_t size;
    uint32_t timestep;
    void* allocStack[ALLOC_STACK_DEPTH];
};

struct VirtualHeapItem{
    AllocInfo info;
    VirtualHeapItem* next_free_item;
};
class VirtualHeap
{
public:
    static VirtualHeap* GetInstance();
    void Init();
    void Register(void *p, size_t size);
    void UnRegister(void *p);
    void ScanMem();

private:
    VirtualHeap(/* args */);
    ~VirtualHeap();
    static VirtualHeap* mInstance;

    VirtualHeapItem* mItems;
    VirtualHeapItem* mpCurrentFreeItem;
    size_t mMaxItemCount;
    bool mIsInit;
    std::mutex mMutex;
    std::unordered_map<void*, VirtualHeapItem*> mMapPtrItem;
};




#endif