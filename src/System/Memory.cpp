#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>

#include "System/Memory.hpp"

static JKRExpHeap* sRootHeap;
JKRExpHeap* sSystemHeap;
static JKRExpHeap* sGameHeap;
JKRExpHeap* sUnusedHeap;
static void* sGXBaseBuffer;
static GXFifoObj* sGXInitFifoObj;

static u8 sCurHeapGroupId = 1;

void initializeGX() {
    getSystemHeap()->changeGroupID(1);
    sGXBaseBuffer = JKRAllocFromSysHeap( 0x80000, 0x20);
    sGXInitFifoObj = GXInit(sGXBaseBuffer,  0x80000);
}

//https://decomp.me/scratch/RvI1x
void initHeaps() {
    sRootHeap = JKRExpHeap::createRoot(1, false);
    s32 size = sRootHeap->getFreeSize();
    void* addr = sRootHeap->alloc(size, 4);

    //Some struct copying code....

    DCStoreRange(addr, size);
    JKRFree(addr);
    sSystemHeap = JKRExpHeap::create(0x6ac000, sRootHeap, false);
    sGameHeap = JKRExpHeap::create(sRootHeap->getFreeSize(), nullptr, false);

    getSystemHeap()->becomeSystemHeap();
    getSystemHeap()->becomeCurrentHeap();
    setCurHeapGroupId(0x1A);
}

// https://decomp.me/scratch/fkjrQ
void* allocMem(u32 size, int alignment) {
    void* data = JKRGetCurrentHeap()->alloc(size, alignment);
    JKRGetCurrentHeap()->getTotalFreeSize();
    JKRGetCurrentHeap()->getFreeSize();

    JKRHeap* curHeap = JKRGetCurrentHeap();

    JKRHeap::sCurrentHeap->getTotalFreeSize();
    curHeap->getFreeSize();
    return data;
}

void freeMem(void* ptr) {
    JKRHeap::free(ptr, nullptr);
}

void freeHeapGroups(u8 groupID) {
    for (s32 i = 1; i <= groupID; i++) {
        sGameHeap->getUsedSize(i);
        sGameHeap->freeGroup(i);
    }
}

u8 setCurHeapGroupId(u8 param_1) {
    sCurHeapGroupId = param_1;

    getSystemHeap()->changeGroupID(param_1);
    return sGameHeap->changeGroupID(param_1);
}

u8 getCurHeapGroupId() {
    return sCurHeapGroupId;
}

void becomeGameHeapCurrent() {
    sGameHeap->becomeCurrentHeap();
}

s32 getGameHeapFreeSize() {
    return sGameHeap->getFreeSize();
}
