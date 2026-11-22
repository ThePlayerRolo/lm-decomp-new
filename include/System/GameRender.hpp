#ifndef _8000AC48_HPP
#define _8000AC48_HPP

#include <types.h>

struct PerFrameBuffer {
    u8* mBuffers[2];
    u8* mCurrentBufferEnd;
    u32 mSize;
    u32 mBufferIdx;
};

// Unsure of return types / args. should validate these
void fn_8000AC48();
void initPerFrameBuffer();
void freePerFrameBuffer();
void swapPerFrameBuffer();
s32 getViewPortCount();
void setViewPortCount(s32);
void setViewPortScissor();

// Definitely some custom struct
extern PerFrameBuffer sPerFrameBuffer;

#endif
