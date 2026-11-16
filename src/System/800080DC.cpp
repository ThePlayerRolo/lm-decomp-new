#include <dolphin/gx/GXFrameBuffer.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXTexture.h>

#include "System/800080DC.hpp"
#include "System/DisplayUtil.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "System/ResetGX.hpp"
#include "dolphin/gx/GXStruct.h"

struct SomeUnk {
    SomeUnk(); // fn_80039464()
    ~SomeUnk(); // fn_80039550()
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    u8 temp[0x18C];
};

SomeUnk lbl_803A3674;
SomeOtherUnk lbl_803A3810;
void* lbl_804D8070;

void fn_800080DC(SomeOtherUnk* param_1) {

    if (param_1->_0 != 8) {
        return;
    }

    setDoubleBuffered(true);
    fn_80039628(&lbl_803A3674);
    param_1->_0 = 3;
}

void fn_8000812C(SomeOtherUnk* param_1) {
    if (fn_80039770(&lbl_803A3674) == 0) {
        return;
    }

    switch (param_1->_0) {
        case 1:
            param_1->_0 = 8;
            break;
        case 2:
            break;
        case 3:
            param_1->_0 = 0;
            break;
    }
}

void fn_800081A8(SomeOtherUnk* param_1) {
    GXTexObj gObj;
    resetGXState();

    switch (param_1->_0) {
        case 4:
            fn_800395BC(&lbl_803A3674, param_1->_4, param_1->_8);
            setDoubleBuffered(false);
            lbl_804D8070 = getPrevMainFrameBuffer();
            GXSetTexCopySrc(0x0, 0x0, 0x280, 0x1E0);
            GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB565, GX_FALSE);
            GXSetCopyClamp(static_cast<GXFBClamp>((GX_CLAMP_TOP | GX_CLAMP_BOTTOM)));
            GXCopyTex(lbl_804D8070, 0x0);
            GXPixModeSync();
            GXInitTexObj(&gObj, lbl_804D8070, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            param_1->_0 = 1;
            fn_80039C74(&lbl_803A3674, &gObj);
            break;
        case 1:
            GXInitTexObj(&gObj, lbl_804D8070, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            fn_80039C74(&lbl_803A3674, &gObj);
            break;
        case 3:
        case 8:
            GXInitTexObj(&gObj, lbl_804D86BC, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            fn_80039C74(&lbl_803A3674, &gObj);
            break;
    }
}

void fn_80008394() {
    lbl_803A3810._0 = 4;
}

void fn_800083A4(u32 param_1) {
    lbl_803A3810._4 = param_1;
}

void fn_800083B4(u32 param_1) {
    lbl_803A3810._8 = param_1;
}
