#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

#include "System/DisplayUtil.hpp"
#include "System/Memory.hpp"
#include "Unsorted/GamePad.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "Unsorted/80009B80.hpp"
#include "dolphin/os/OSMessage.h"
#include "macros.h"

dummy_float_data()

struct FrameSync {
    /* 0x00 */ u32 mLastRetraceCount;
    /* 0x04 */ u32 mFrameRateDivisor; // 1 = 60fps, 2 = 30fps
    /* 0x08 */ OSMessageQueue mMsgQueue;
    /* 0x28 */ OSMessage mMsg;  // Msg
};

// .bss start
FrameSync sFrameSync;
GXRenderModeObj sIntRenderModeObj;
// .bss end

// .data start

// clang-format off
GXRenderModeObj sProgRenderModeObj = {
    VI_TVMODE_NTSC_PROG,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFBMODE_SF,
    0,
    0,
    {
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
    },
    { 0,0, 26,12,26, 0,0  }
};
// clang-format on

// .data end

// .sbss start
JUTDirectPrint* sDirectPrintManager;
u8 sRenderMode;
DisplayState sDisplayState;
void* sFrameBufferA;
void* sFrameBufferB;
void* sMainFrameBuffer;
void* sPrevMainFrameBuffer;
void* sFrameBuffers[2];
GXRenderModeObj* sCurRenderModeObj;
ProgressiveScanState sProgressiveScanPromptState; 
s32 sProgressiveScanChoice; // Pending choice from player, actual result is sRenderMode
s32 sProgressiveScanMsgTimer;
// .sbss end

// .sdata start
GXRenderModeObj* sDefaultRenderModes[2] = {
    &sIntRenderModeObj,
    &sProgRenderModeObj,
};
// .sdata end

static void configureRenderDisplay();
static void postRetraceCallback(u32 retraceCount);

static void initDisplayInternal(DisplayState* dst) {
    VISetBlack(TRUE);
    sIntRenderModeObj = GXNtsc480IntDf;
    sIntRenderModeObj.vfilter[0] = 6;
    sIntRenderModeObj.vfilter[1] = 0;
    sIntRenderModeObj.vfilter[5] = 0;
    sIntRenderModeObj.vfilter[6] = 6;
    sIntRenderModeObj.vfilter[2] = 20;
    sIntRenderModeObj.vfilter[3] = 12;
    sIntRenderModeObj.vfilter[4] = 20;
    OSGetTime();

    OSInitMessageQueue(&sFrameSync.mMsgQueue, &sFrameSync.mMsg, 1);
    sFrameSync.mLastRetraceCount = VIGetRetraceCount();
    sFrameSync.mFrameRateDivisor = 1;

    dst->mFlags = 0;
    dst->mIsDoubleBuffered = true;
    dst->mBufferIndex = 0;
    sMainFrameBuffer = nullptr;
    sSystemHeap->changeGroupID(2);

    u32 frameBufferSize = 0x96000;
    if (sFrameBufferA == nullptr) {
        sFrameBufferA = JKRAllocFromHeap(nullptr, frameBufferSize, 0x20);
    }

    if (sFrameBufferA != nullptr) {
        DCInvalidateRange(sFrameBufferA, frameBufferSize);
    }

    if (dst->mIsDoubleBuffered == true) {
        if (sFrameBufferB == nullptr) {
            sFrameBufferB = JKRAllocFromHeap(nullptr, frameBufferSize, 0x20);
        }

        if (sFrameBufferB != nullptr) {
            DCInvalidateRange(sFrameBufferB, frameBufferSize);
        }
        sMainFrameBuffer = sFrameBufferA;
    } else {
        sFrameBufferB = sMainFrameBuffer = sFrameBufferA;
    }

    void* firstBuffer = sMainFrameBuffer;
    sFrameBuffers[0] = sFrameBufferA;
    sFrameBuffers[1] = sFrameBufferB;

    VISetNextFrameBuffer(firstBuffer);
    sCurRenderModeObj = &sIntRenderModeObj;
    configureRenderDisplay();
    VISetPostRetraceCallback(postRetraceCallback);

    sSystemHeap->changeGroupID(26);
}

void postRetraceCallback(u32 retraceCount) {
    if (retraceCount - sFrameSync.mLastRetraceCount >= sFrameSync.mFrameRateDivisor) {
        // Reports "DONE" once the frame rate divisor retraces have passed since the frames started.
        OSSendMessage(&sFrameSync.mMsgQueue, OSMessage(0x444F4E45), OS_MESSAGE_NOBLOCK);
    }
}

static void setNextVIFrameBuffer(DisplayState* pSettings) {
    // TODO: Remove this
    FORCE_DONT_INLINE;
    if ((pSettings->mFlags & 1)) {
        VISetBlack(GX_FALSE);
    } else {
        VISetBlack(GX_TRUE);
    }

    VISetNextFrameBuffer(sMainFrameBuffer);
    VIFlush();
    if (pSettings->mIsDoubleBuffered) {
        pSettings->mBufferIndex ^= 1;
        sMainFrameBuffer = sFrameBuffers[pSettings->mBufferIndex];
    }
}

void resetRenderDisplay() {
    GXSetCopyClear(sReset, 0xFFFFFF);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetDispCopySrc(0, 0, sCurRenderModeObj->fbWidth, sCurRenderModeObj->efbHeight);
    GXSetDispCopyDst(sCurRenderModeObj->fbWidth, sCurRenderModeObj->efbHeight);
    GXSetDispCopyYScale((f32)sCurRenderModeObj->xfbHeight / (f32)sCurRenderModeObj->efbHeight);
    GXSetCopyFilter(sCurRenderModeObj->aa, sCurRenderModeObj->sample_pattern, GX_TRUE, sCurRenderModeObj->vfilter);
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetDispCopyGamma(GX_GM_1_0);
    if (sCurRenderModeObj->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
        GXSetDither(GX_FALSE);
    } else {
        GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
        GXSetDither(GX_TRUE);
    }
}

static void configureRenderDisplay() {
    VIConfigure(sCurRenderModeObj);
    resetRenderDisplay();
    GXCopyDisp(sMainFrameBuffer, GX_TRUE);
    GXCopyDisp(sMainFrameBuffer, GX_TRUE);
    GXFlush();
    GXDrawDone();
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}

void initDisplay() {
    initDisplayInternal(&sDisplayState);
}

void beginFrame() {
    GXInvalidateTexAll();
    GXInvalidateVtxCache();
    GXSetScissor(0, 0, sCurRenderModeObj->fbWidth, sCurRenderModeObj->xfbHeight);
}

void endFrameSingleBuffered() {
    GXDrawDone();
    OSReceiveMessage(&sFrameSync.mMsgQueue, nullptr, OS_MESSAGE_BLOCK);
    sFrameSync.mLastRetraceCount = VIGetRetraceCount();
    VIWaitForRetrace();
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);

    if (sMainFrameBuffer != nullptr) {
        GXCopyDisp(sMainFrameBuffer, GX_TRUE);
    }

    if ((sDisplayState.mFlags & 1)) {
        VISetBlack(GX_FALSE);
    } else {
        VISetBlack(GX_TRUE);
    }

    VISetNextFrameBuffer(sMainFrameBuffer);
    VIFlush();

    if (sDisplayState.mIsDoubleBuffered) {
        sDisplayState.mBufferIndex ^= 1;
        sMainFrameBuffer = sFrameBuffers[sDisplayState.mBufferIndex];
    }

    GXFlush();
}

void endFrame() {
    resetRenderDisplay();
    if (sDisplayState.mIsDoubleBuffered == true) {
        GXDrawDone();
        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_TRUE);
        GXCopyDisp(sMainFrameBuffer, GX_TRUE);
        GXFlush();
        setNextVIFrameBuffer(&sDisplayState);
        OSReceiveMessage(&sFrameSync.mMsgQueue, NULL, OS_MESSAGE_BLOCK);
        sFrameSync.mLastRetraceCount = VIGetRetraceCount();
    } else {
        endFrameSingleBuffered();
    }

    void* frameBuf = sMainFrameBuffer;
    JUTDirectPrint::getManager()->changeFrameBuffer(frameBuf, 640, 480);
}

void applyRenderMode() {
    if (sCurRenderModeObj != sDefaultRenderModes[sRenderMode]) {
        sCurRenderModeObj = sDefaultRenderModes[sRenderMode];
        configureRenderDisplay();
    }
}

void defaultOrthoView() {
    f32 x = 0.0f;
    f32 y = 0.0f;

    GXSetScissor(0, 0, sCurRenderModeObj->fbWidth, sCurRenderModeObj->xfbHeight);
    GXSetViewportJitter(0.0f, 0.0f, sCurRenderModeObj->fbWidth, sCurRenderModeObj->xfbHeight, 0.0f, 1.0f, 1);
    Mtx44 orthoMtx;
    MTXOrtho(orthoMtx, -y, 480.0f - y, -x, sCurRenderModeObj->fbWidth - x, -1.0f, 1000.0f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_NONE);
    GXLoadPosMtxImm(sDefaultMtx, 0);
    GXLoadNrmMtxImm(sDefaultMtx, 0);
    GXLoadTexMtxImm(sDefaultMtx, 60, GX_MTX2x4);
    GXSetCurrentMtx(0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, 15);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_CLR_RGBA, GX_RGBX8, 15);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, sWhite);
    GXSetChanAmbColor(GX_COLOR0A0, sWhite);
    GXSetChanMatColor(GX_COLOR1A1, sWhite);
    GXSetChanAmbColor(GX_COLOR1A1, sWhite);
    GXSetTevKColor(GX_KCOLOR0, sWhite);
    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetDstAlpha(GX_FALSE, 0xFF);
}

void setViewportJitter(f32 left, f32 top, f32 width, f32 height, f32 near, f32 far) {
    f32 widthScale = sCurRenderModeObj->fbWidth / 640.0f;
    f32 heightScale = 1.0f;

    if (sCurRenderModeObj->field_rendering) {
        GXSetViewportJitter(left * widthScale, top * heightScale, width * widthScale, height * heightScale, near, far, VIGetNextField());
    } else {
        GXSetViewportJitter(left * widthScale, top * heightScale, width * widthScale, height * heightScale, near, far, 1);
    }
}

void setDisplayFlags(u16 flags) {
    sDisplayState.mFlags |= flags;
}

void setFrameRateDivisor(s32 divisor) {
    sFrameSync.mFrameRateDivisor = divisor;
}

void setDoubleBuffered(bool enable) {
    sDisplayState.mIsDoubleBuffered = enable;
    if (enable == true) {
        sDisplayState.mBufferIndex ^= 1;
        sDisplayState.mBufferIndex &= sDisplayState.mIsDoubleBuffered;
        sMainFrameBuffer = sFrameBuffers[sDisplayState.mBufferIndex];
        return;
    }

    sPrevMainFrameBuffer = sMainFrameBuffer;

    if (sPrevMainFrameBuffer == sFrameBufferA)
        sMainFrameBuffer = sFrameBufferB;
    else
        sMainFrameBuffer = sFrameBufferA;
}

void* getMainFrameBuffer() {
    return sMainFrameBuffer;
}

void* getPrevMainFrameBuffer() {
    return sPrevMainFrameBuffer;
}

u32 getFrameRateDivisor() {
    return sFrameSync.mFrameRateDivisor;
}

void setIntRenderModeVFilter(s32 vfilterVal) {
    sIntRenderModeObj.vfilter[0] = vfilterVal;
    sIntRenderModeObj.vfilter[6] = vfilterVal;
    sIntRenderModeObj.vfilter[2] = 26 - vfilterVal;
    sIntRenderModeObj.vfilter[4] = 26 - vfilterVal;
}

void checkProgressiveScanPrompt() {
    if (VIGetDTVStatus() != 0) {
        if (sGamePad->testButton(JUTGamePad::B) != 0 || OSGetProgressiveMode() != 0) {
            sProgressiveScanPromptState = PSCAN_ASKING;
            sProgressiveScanChoice = 1;
            return;
        }

        OSSetProgressiveMode(0);
        return;
    }

    OSSetProgressiveMode(0);
}

void updateProgressiveScanPrompt() {
    if (sProgressiveScanPromptState != 1)
        return;

    if (sGamePad->testRepeat(JUTGamePad::PRESS_LEFT)) {
        sProgressiveScanChoice ^= 1;
    }

    if (sGamePad->testRepeat(JUTGamePad::PRESS_RIGHT)) {
        sProgressiveScanChoice ^= 1;
    }

    fn_80047444(sProgressiveScanChoice);
}

void tickProgressiveMessage() {
    static u32 lbl_804D8064 = 0;

    if (sProgressiveScanPromptState != 2)
        return;

    if (sProgressiveScanMsgTimer <= 0) {
        sProgressiveScanPromptState = PSCAN_OFF;
        return;
    }

    sProgressiveScanMsgTimer--;
    fn_80047444(sProgressiveScanChoice + 2);
}

void applyProgressiveChoice() {
    if (sProgressiveScanPromptState != 1)
        return;

    if (sProgressiveScanChoice == OSGetProgressiveMode()) {
        sProgressiveScanMsgTimer = 0;
        sProgressiveScanPromptState = PSCAN_OFF;
    } else {
        sProgressiveScanMsgTimer = 90;
        sProgressiveScanPromptState = PSCAN_SHOW_RESULT;
    }
    OSSetProgressiveMode(sProgressiveScanChoice);
    sRenderMode = OSGetProgressiveMode();
}
