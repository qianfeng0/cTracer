#include <malloc.h>
#include <string.h>

#include "common_log.h"
#include "unwind_backtrace.h"

#include "virtual_heap.h"

#define VIRTUAL_HEAP_DEBUG 1

const size_t kMaxHeapSize = 8 * 1024 * 1024;

VirtualHeap* VirtualHeap::mInstance = nullptr;

VirtualHeap::VirtualHeap():
mItems(nullptr),
mpCurrentFreeItem(nullptr),
mMaxItemCount(0),
mIsInit(false)
{
}

VirtualHeap::~VirtualHeap()
{
}

VirtualHeap* VirtualHeap::GetInstance()
{
    if (mInstance == nullptr){
        mInstance = new VirtualHeap;
        mInstance->Init();
    }

    return mInstance;
}

void VirtualHeap::Init()
{
    mItems = (VirtualHeapItem*)malloc(kMaxHeapSize);
    if (mItems == nullptr){
        LOGE("VirtualHeap::Init malloc: %zu error\n", kMaxHeapSize);
        return;
    }

    mMaxItemCount = kMaxHeapSize / sizeof(VirtualHeapItem);
    if (mMaxItemCount == 0)
        return;

    memset(mItems, 0, kMaxHeapSize);
    for (size_t i = 0; i < mMaxItemCount - 1; i++){
        mItems[i].next_free_item = &mItems[i+1];
    }
    mpCurrentFreeItem = &mItems[0];

    mIsInit = true;
    LOGI("VirtualHeap::Init ok, mMaxItemCount:%zu, VirtualHeapItem size: %zu\n", mMaxItemCount, sizeof(VirtualHeapItem));
}

void VirtualHeap::Register(void *p, size_t size)
{
    // LOGD("VirtualHeap::Register, p: %p, size:%zu\n", p, size);

    std::lock_guard<std::mutex> lock(mMutex);

    if (mpCurrentFreeItem == nullptr){
        LOGE("VirtualHeap::Register heap item is full !!!\n");
        return;
    }

    if (mpCurrentFreeItem->info.alloc_ptr != nullptr){
        LOGE("VirtualHeap::Register heap item is not null %p ,%p !!!\n", mpCurrentFreeItem, mpCurrentFreeItem->info.alloc_ptr);
    }

    //alloc info
    mpCurrentFreeItem->info.alloc_ptr = p;
    mpCurrentFreeItem->info.size = size;
    mpCurrentFreeItem->info.timestep = 0;
    StackWrap stack_warp = StackWrap(mpCurrentFreeItem->info.allocStack,
                                    ARRAY_SIZE(mpCurrentFreeItem->info.allocStack),
                                    2);
    get_stack(&stack_warp);
    // print_stack(mpCurrentFreeItem->info.allocStack, ARRAY_SIZE(mpCurrentFreeItem->info.allocStack));

#if VIRTUAL_HEAP_DEBUG
    auto got = mMapPtrItem.find(p);
    if (got != mMapPtrItem.end()){
        LOGD("VirtualHeap::Register error mMapPtrItem.find, p: %p, size:%zu\n", p, size);
        abort();
    }
#endif

    mMapPtrItem.insert({p, mpCurrentFreeItem});
    //next free item;
    mpCurrentFreeItem = mpCurrentFreeItem->next_free_item;

    return;
}

void VirtualHeap::UnRegister(void *p)
{
    // LOGD("VirtualHeap::UnRegister, p: %p\n", p);

    std::lock_guard<std::mutex> lock(mMutex);

    auto got = mMapPtrItem.find(p);
    if (got == mMapPtrItem.end()){
        LOGE("VirtualHeap::UnRegister mMapPtrItem.not find, p: %p\n", p);
        return;
    }

    VirtualHeapItem* item_ptr = got->second;

    if ((item_ptr->info.alloc_ptr != p) ||
        (((uintptr_t)item_ptr - (uintptr_t)mItems) % sizeof(VirtualHeapItem) != 0)){
        LOGE("VirtualHeap::UnRegister error, alloc_ptr:%p, %p, id(%zu, %zu)\n",
            item_ptr->info.alloc_ptr, p,
            ((uintptr_t)item_ptr - (uintptr_t)mItems) / sizeof(VirtualHeapItem),
            ((uintptr_t)item_ptr - (uintptr_t)mItems) % sizeof(VirtualHeapItem));
    }

    mMapPtrItem.erase(p);
    memset(item_ptr, 0, sizeof(VirtualHeapItem));

    // set current free item
    item_ptr->next_free_item = mpCurrentFreeItem;
    mpCurrentFreeItem = item_ptr;
    return;
}

void VirtualHeap::ScanMem()
{
    std::lock_guard<std::mutex> lock(mMutex);

    for (auto iter : mMapPtrItem){
        AllocInfo* info = &iter.second->info;
        LOGD("alloc_ptr:%p \t size:%zu, time:%u\n", info->alloc_ptr, info->size, info->timestep);
        LOGD("stack:\n");
        for (size_t i = 0; i < ARRAY_SIZE(info->allocStack); i++){
            LOGD("\t %p", info->allocStack[i]);
        }
        LOGD("\n");
    }
}