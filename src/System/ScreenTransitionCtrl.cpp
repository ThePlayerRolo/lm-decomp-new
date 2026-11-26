#include <dolphin/gx/GXFrameBuffer.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXStruct.h>

#include "System/ScreenTransitionCtrl.hpp"
#include "System/DisplayUtil.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "System/ResetGX.hpp"


static ScreenTransition sScreenTransition;
ScreenTransitionCtrl sScreenTransitionCtrl;
static void* sLastFrameCopy;

void ScreenTransitionCtrl::startTransitionIn() {

    if (mState != 8) {
        return;
    }

    setDoubleBuffered(true);
    sScreenTransition.startTransitionIn();
    mState = SCREEN_TRANSITION_IN;
}

void ScreenTransitionCtrl::update() {
    if (sScreenTransition.update() == 0) {
        return;
    }

    switch (mState) {
        case SCREEN_TRANSITION_OUT:
            mState = SCREEN_TRANSITION_DONE;
            break;
        case SCREEN_TRANSITION_UNUSED_2:
            break;
        case SCREEN_TRANSITION_IN:
            mState = SCREEN_TRANSITION_IDLE;
            break;
    }
}

void ScreenTransitionCtrl::draw() {
    GXTexObj gObj;
    resetGXState();

    switch (mState) {
        case SCREEN_TRANSITION_REQUESTED:
            sScreenTransition.switchTransition(mType, mLength);
            setDoubleBuffered(false);
            sLastFrameCopy = getPrevMainFrameBuffer();
            GXSetTexCopySrc(0x0, 0x0, 0x280, 0x1E0);
            GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB565, GX_FALSE);
            GXSetCopyClamp(static_cast<GXFBClamp>((GX_CLAMP_TOP | GX_CLAMP_BOTTOM)));
            GXCopyTex(sLastFrameCopy, 0x0);
            GXPixModeSync();
            GXInitTexObj(&gObj, sLastFrameCopy, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            mState = SCREEN_TRANSITION_OUT;
            sScreenTransition.draw(&gObj);
            break;
        case SCREEN_TRANSITION_OUT:
            GXInitTexObj(&gObj, sLastFrameCopy, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            sScreenTransition.draw(&gObj);
            break;
        case SCREEN_TRANSITION_IN:
        case SCREEN_TRANSITION_DONE:
            GXInitTexObj(&gObj, lbl_804D86BC, 0x280, 0x1E0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            sScreenTransition.draw(&gObj);
            break;
    }
}

void ScreenTransitionCtrl::requestTransition() {
    sScreenTransitionCtrl.setState(SCREEN_TRANSITION_REQUESTED);
}

void ScreenTransitionCtrl::setTransitionType(ScreenTransitionType param_1) {
    sScreenTransitionCtrl.setType(param_1);
}

void ScreenTransitionCtrl::setTransitionLength(s32 param_1) {
    sScreenTransitionCtrl.setLength(param_1);
}
