#include <dolphin/gx/GXCull.h>

#include "System/GameRender.hpp"
#include "System/80008418.hpp"
#include "System/DisplayUtil.hpp"
#include "System/Memory.hpp"

PerFrameBuffer sPerFrameBuffer;

static s32 sViewportCount = 1;

void initPerFrameBuffer() {
    sPerFrameBuffer.mBufferIdx = 0;
    sPerFrameBuffer.mSize = 0x200;
    sPerFrameBuffer.mBuffers[0] = reinterpret_cast<u8*>(allocMem(0x400, 32));
    sPerFrameBuffer.mBuffers[1] = sPerFrameBuffer.mBuffers[0] + 0x200;
}

void freePerFrameBuffer() {
    freeMem(sPerFrameBuffer.mBuffers[0]);
}

void swapPerFrameBuffer() {
    sPerFrameBuffer.mBufferIdx ^= 1;
    sPerFrameBuffer.mCurrentBufferEnd = reinterpret_cast<u8*>(
        reinterpret_cast<u32>(sPerFrameBuffer.mBuffers[sPerFrameBuffer.mBufferIdx]) + sPerFrameBuffer.mSize);
}

s32 getViewPortCount() {
    return sViewportCount;
}

void setViewPortCount(s32 count) {
    sViewportCount = count;
}

void setViewPortScissor(u32 x, u32 y, u32 w, u32 h) {
    lbl_803A3820.mViewport.x1 = x;
    lbl_803A3820.mViewport.y1 = y;
    lbl_803A3820.mViewport.x2 = w;
    lbl_803A3820.mViewport.y2 = h;
    setViewportJitter(x, y, w, h, 0.0f, 1.0f);
    GXSetScissor(x, y, w, h);
}
