#include <dolphin/gx/GXCull.h>

#include "System/8000AC48.hpp"
#include "System/80008418.hpp"
#include "System/DisplayUtil.hpp"
#include "System/Memory.hpp"

SomeDoubleBuffer lbl_803A3A80;

static s32 lbl_804CFF90 = 1;

void fn_8000AD48() {
    lbl_803A3A80.mBufferIdx = 0;
    lbl_803A3A80.mSize = 0x200;
    lbl_803A3A80.mBuffers[0] = reinterpret_cast<u8*>(allocMem(0x400, 32));
    lbl_803A3A80.mBuffers[1] = lbl_803A3A80.mBuffers[0] + 0x200;
}

void fn_8000ADA0() {
    freeMem(lbl_803A3A80.mBuffers[0]);
}

void fn_8000ADCC() {
    lbl_803A3A80.mBufferIdx ^= 1;
    lbl_803A3A80.mCurrentBufferEnd = reinterpret_cast<u8*>(
        reinterpret_cast<u32>(lbl_803A3A80.mBuffers[lbl_803A3A80.mBufferIdx]) + lbl_803A3A80.mSize);
}

s32 fn_8000ADFC() {
    return lbl_804CFF90;
}

void fn_8000AE04(s32 param_1) {
    lbl_804CFF90 = param_1;
}

void fn_8000AE0C(u32 x, u32 y, u32 w, u32 h) {
    lbl_803A3820._1EC = x;
    lbl_803A3820._1F0 = y;
    lbl_803A3820._1F4 = w;
    lbl_803A3820._1F8 = h;
    setViewportJitter(x, y, w, h, 0.0f, 1.0f);
    GXSetScissor(x, y, w, h);
}
