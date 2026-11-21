#ifndef _8000AC48_HPP
#define _8000AC48_HPP

#include <types.h>

struct SomeDoubleBuffer {
    u8* mBuffers[2];
    u8* mCurrentBufferEnd;
    u32 mSize;
    u32 mBufferIdx;
};

// Unsure of return types / args. should validate these
void fn_8000AC48();
void fn_8000AD48(); // Allocs Memory for lbl_803A3A80
void fn_8000ADA0(); // Just a freeMem call from lbl_803A3A80
void fn_8000ADCC();
s32 fn_8000ADFC();
void fn_8000AE04(s32);
void fn_8000AE0C();

// Definitely some custom struct
extern SomeDoubleBuffer lbl_803A3A80;

#endif
