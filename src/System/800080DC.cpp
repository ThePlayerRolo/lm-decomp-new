#include <dolphin/gx/GXFrameBuffer.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXStruct.h>

#include "System/800080DC.hpp"
#include "System/DisplayUtil.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "System/ResetGX.hpp"

class Struct800080DCTwo {
    public:
        Struct800080DCTwo(); // fn_80039464()
        ~Struct800080DCTwo(); // fn_80039550()
        u32 _0;
        u32 _4;
        u32 _8;
        u32 _C;
        u8 temp[0x18C];
};

Struct800080DCTwo lbl_803A3674;
Struct800080DCOne lbl_803A3810;
void* lbl_804D8070;

void Struct800080DCOne::fn_800080DC() {

    if (mState != 8) {
        return;
    }

    setDoubleBuffered(true);
    fn_80039628(&lbl_803A3674);
    mState = STATE_80DC_3;
}

void Struct800080DCOne::fn_8000812C() {
    if (fn_80039770(&lbl_803A3674) == 0) {
        return;
    }

    switch (mState) {
        case STATE_80DC_1:
            mState = STATE_80DC_8;
            break;
        case STATE_80DC_2:
            break;
        case STATE_80DC_3:
            mState = STATE_80DC_DEFAULT;
            break;
    }
}

void Struct800080DCOne::fn_800081A8() {
    GXTexObj gObj;
    resetGXState();

    switch (mState) {
        case STATE_80DC_4:
            fn_800395BC(&lbl_803A3674, _4, _8);
            setDoubleBuffered(false);
            lbl_804D8070 = getPrevMainFrameBuffer();
            GXSetTexCopySrc(0x0, 0x0, 0x280, 0x1E0);
            GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB565, GX_FALSE);
            GXSetCopyClamp(static_cast<GXFBClamp>((GX_CLAMP_TOP | GX_CLAMP_BOTTOM)));
            GXCopyTex(lbl_804D8070, 0x0);
            GXPixModeSync();
            GXInitTexObj(&gObj, lbl_804D8070, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            mState = STATE_80DC_1;
            fn_80039C74(&lbl_803A3674, &gObj);
            break;
        case STATE_80DC_1:
            GXInitTexObj(&gObj, lbl_804D8070, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            fn_80039C74(&lbl_803A3674, &gObj);
            break;
        case STATE_80DC_3:
        case STATE_80DC_8:
            GXInitTexObj(&gObj, lbl_804D86BC, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            fn_80039C74(&lbl_803A3674, &gObj);
            break;
    }
}

void fn_80008394() {
    lbl_803A3810.setState(STATE_80DC_4);
}

void fn_800083A4(u32 param_1) {
    lbl_803A3810.setUnk4(param_1);
}

void fn_800083B4(u32 param_1) {
    lbl_803A3810.setUnk8(param_1);
}
