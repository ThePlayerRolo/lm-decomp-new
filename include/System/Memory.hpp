#ifndef MEMORY_HPP
#define MEMORY_HPP

// TODO: Could be apart of main.cpp
#include <types.h>

class JKRExpHeap;

void initializeGX();
void initHeaps();
void* allocMem(u32 size, int alignment);
void freeMem(void* ptr); //Possibly JKRFree being uninlined
void freeHeapGroups(u8 groupID);
u8 setCurHeapGroupId(u8 param_1);
u8 getCurHeapGroupId();
void becomeGameHeapCurrent();
s32 getGameHeapFreeSize();

extern JKRExpHeap* sSystemHeap;
extern JKRExpHeap* sUnusedHeap;

inline JKRExpHeap* getSystemHeap() { return sSystemHeap; }

#endif
