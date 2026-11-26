#include <JSystem/J2D/J2DOrthoGraph.hpp>
#include <JSystem/JUtility/JUTColor.hpp>
#include <JSystem/JUtility/JUTTexture.hpp>
#include <dolphin/gx.h>

#include "System/Scenes/ScreenTransition.hpp"
#include "System/80008418.hpp"
#include "System/DisplayUtil.hpp"

dummy_float_data();

static ScreenTransition sUnusedScreenTransition; // seems to be unused in the final game

ScreenTransition::ScreenTransition() : mTexture() {
    mCurrent = SCREEN_TRANSITION_NONE;
    mNext = SCREEN_TRANSITION_NONE;
    mPhase = 0;
    mCurrentFrame = 0;
    _10 = 0;
    _190 = 0;
    mColor.r = 0;
    mColor.g = 0;
    mColor.b = 0;
    mColor.a = 255;
    mLength = 30;
    mDelayFrames = 0;
}

ScreenTransition::~ScreenTransition() { }

void ScreenTransition::switchTransition(ScreenTransitionType nextTransition, s16 length) {
    mPhase = SCREEN_PHASE_OUT;

    mNext = (nextTransition > SCREEN_TRANSITION_WHITE_FADE) ? SCREEN_TRANSITION_FADE : nextTransition;

    mCurrentFrame = 0;
    mLength = length;
    setTransitionSettings();
    switchToNextTransition();
    mDelayFrames = 0;
}

void ScreenTransition::startTransitionIn() {
    mPhase = SCREEN_PHASE_IN;

    switch (mCurrent) {
        case SCREEN_TRANSITION_BLACK:
            mCurrent = SCREEN_TRANSITION_FADE;
            break;
        default:
            break;
    }

    // Gotta shout out m2c for helping with the order here :P
    switch (mCurrent) {
        case SCREEN_TRANSITION_BLACK:
        case SCREEN_TRANSITION_SIDEWIPE:
            mCurrentFrame = 0;
            break;
        case SCREEN_TRANSITION_ZOOM_ECHO:
        case SCREEN_TRANSITION_FADE:
            mCurrentFrame = mLength;
            break;
        default:
            mCurrentFrame = 255;
    }

    mDelayFrames = 3;
    switchToNextTransition();
}

void ScreenTransition::setTransitionSettings() {
    switch (mNext) {
        case SCREEN_TRANSITION_BLACK:
            mCurrentFrame = mLength;
            break;
        case SCREEN_TRANSITION_BLACK_FADE:
            mColor.r = 0;
            mColor.g = 0;
            mColor.b = 0;
            mColor.a = 255;
            mNext = SCREEN_TRANSITION_FADE;
            mCurrentFrame = 0;
            break;
        case SCREEN_TRANSITION_WHITE_FADE:
            mColor.r = 255;
            mColor.g = 255;
            mColor.b = 255;
            mColor.a = 255;
            mNext = SCREEN_TRANSITION_FADE;
            mCurrentFrame = 0;
            break;
        default:
            mCurrentFrame = 0;
    }
}

void ScreenTransition::switchToNextTransition() {
    if (mNext == SCREEN_TRANSITION_NONE) return;

    mCurrent = mNext;
    mNext = SCREEN_TRANSITION_NONE;
}

BOOL ScreenTransition::update() {
    if (mDelayFrames > 0) {
        mDelayFrames--;
        return FALSE;
    }

    switch (mCurrent) {
        case SCREEN_TRANSITION_FADE:
            switch (mPhase) {
                case SCREEN_PHASE_OUT:
                    mCurrentFrame += getFrameRateDivisor();
                    if (mCurrentFrame >= mLength) {
                        mCurrentFrame = mLength;
                        mPhase = SCREEN_PHASE_DONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_IN:
                    mCurrentFrame -= getFrameRateDivisor();
                    if (mCurrentFrame <= 0) {
                        mCurrentFrame = 0;
                        mCurrent = SCREEN_TRANSITION_NONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_DONE:
                    break;
            }
            break;
        case SCREEN_TRANSITION_SIDEWIPE:
            switch (mPhase) {
                case SCREEN_PHASE_OUT:
                    mCurrentFrame += getFrameRateDivisor();
                    if (mCurrentFrame >= mLength) {
                        mCurrentFrame = mLength;
                        mPhase = SCREEN_PHASE_DONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_IN:
                    mCurrentFrame += getFrameRateDivisor();
                    if (mCurrentFrame >= mLength) {
                        mCurrentFrame = mLength;
                        mCurrent = SCREEN_TRANSITION_NONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_DONE:
                    break;
            }
            break;
        case SCREEN_TRANSITION_IMAGE:
            switch (mPhase) {
                case SCREEN_PHASE_OUT:
                    mCurrentFrame++;
                    if (mCurrentFrame > 1) {
                        mPhase = SCREEN_PHASE_DONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_DONE:
                    mCurrentFrame = 255;
                    break;
                case SCREEN_PHASE_IN:
                    mCurrentFrame -= getFrameRateDivisor() * 10;
                    if (mCurrentFrame <= 0) {
                        mCurrentFrame = 0;
                        mCurrent = SCREEN_TRANSITION_NONE;
                        return TRUE;
                    }
                    break;
            }
            break;
        case SCREEN_TRANSITION_ZOOM_ECHO:
            switch (mPhase) {
                case SCREEN_PHASE_OUT:
                    mCurrentFrame += getFrameRateDivisor();
                    if (mCurrentFrame >= mLength) {
                        mCurrentFrame = mLength;
                        mPhase = SCREEN_PHASE_DONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_IN:
                    mCurrentFrame -= getFrameRateDivisor();
                    if (mCurrentFrame <= 0) {
                        mCurrentFrame = 0;
                        mCurrent = SCREEN_TRANSITION_NONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_DONE:
                    break;
            }
            break;
        case SCREEN_TRANSITION_BLACK:
            switch (mPhase) {
                case SCREEN_PHASE_OUT:
                    mCurrentFrame -= getFrameRateDivisor();
                    if (mCurrentFrame <= 0) {
                        mCurrentFrame = 0;
                        mPhase = SCREEN_PHASE_DONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_IN:
                    mCurrentFrame += getFrameRateDivisor();
                    if (mCurrentFrame >= mLength) {
                        mCurrentFrame = mLength;
                        mCurrent = SCREEN_TRANSITION_NONE;
                        return TRUE;
                    }
                    break;
                case SCREEN_PHASE_DONE:
                    break;
            }
        case SCREEN_TRANSITION_NONE:
        case SCREEN_TRANSITION_BLACK_FADE:
        case SCREEN_TRANSITION_WHITE_FADE:
            break;
    }

    return FALSE;
}

// https://decomp.me/scratch/M8BWa
void ScreenTransition::drawScreenQuad(s32 x, s32 y, s32 w, s32 h) {
    s32 pointRight = x + w;
    s32 pointBottom = y + h;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3s16(x, y, -10);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x0000, 0x0000);

    GXPosition3s16(pointRight, y, -10);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x8000, 0x0000);

    GXPosition3s16(pointRight, pointBottom, -10);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x8000, 0x8000);

    GXPosition3s16(x, pointBottom, -10);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x0000, 0x8000);

    GXEnd();
}

void ScreenTransition::drawScreen(GXTexObj* pScreenTexture) {
    if (pScreenTexture == nullptr) return;

    defaultOrthoView();
    GXLoadTexObj(pScreenTexture, GX_TEXMAP0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_NONE);
    GXColor white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    white.a = 255;
    GXSetChanMatColor(GX_COLOR0A0, white);
    drawScreenQuad(0, 0, 640, 480);
}

// These inlines are needed in order to prevent unwanted initialization in draw due to how switch cases work
inline void ScreenTransition::drawGraph1() {
    J2DOrthoGraph graph(0, 0, 640, 480);
    graph.setPort();
    J2DFillBox(0, 0, 640, 480, JUtility::TColor(mColor.r, mColor.g, mColor.b, (mCurrentFrame * 255) / mLength));
}

inline void ScreenTransition::drawSideWipe() {
    J2DOrthoGraph sidewipe(0, 0, 640, 480);
    sidewipe.setPort();

    if (mPhase == SCREEN_PHASE_OUT) {
        J2DFillBox(0, 0, (mCurrentFrame * 640) / mLength, 480, JUtility::TColor(mColor.r, mColor.g, mColor.b, 255));
    } else {
        J2DFillBox((mCurrentFrame * 640) / mLength, 0, 640, 480, JUtility::TColor(mColor.r, mColor.g, mColor.b, 255));
    }
}

// https://decomp.me/scratch/0eced
void ScreenTransition::draw(GXTexObj* pScreenTexture) {
    defaultOrthoView();
    switch (mCurrent) {
    case SCREEN_TRANSITION_FADE:
        if (mPhase == SCREEN_PHASE_OUT) {
            drawScreen(pScreenTexture);
        }

        drawGraph1();

        switch (mPhase) {
            case SCREEN_PHASE_OUT:
                if (mCurrentFrame >= 255) {
                    mCurrent = SCREEN_TRANSITION_NONE;
                }
                break;
            case SCREEN_PHASE_IN:
                break;
        }
        break;
    case SCREEN_TRANSITION_SIDEWIPE:
        drawSideWipe();
        break;
    case SCREEN_TRANSITION_IMAGE:
        switch (mPhase) {
            case SCREEN_PHASE_OUT:
                break;
            case SCREEN_PHASE_DONE:
                mTexture.draw_8003B0E8(0, 0, mTexture.mTextures[0]->getWidth(), mTexture.mTextures[0]->getHeight());
                break;
            case SCREEN_PHASE_UNK:
                break;
            case SCREEN_PHASE_IN:
                GXSetChanMatColor(GX_COLOR0A0, JUtility::TColor(255, 255, 255, mCurrentFrame));
                mTexture.draw_8003B0E8(0, 0, 640, 480);
                break;
        };
        break;
    case SCREEN_TRANSITION_ZOOM_ECHO: {
        drawGraph1();
        defaultOrthoView();
        GXLoadTexObj(pScreenTexture, GX_TEXMAP0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_NONE);

        s32 currentFrame = mCurrentFrame; // ?

        s32 frame = currentFrame < 5 ? 0 : currentFrame * 8 - 40;
        s32 second =  frame % 60;

        s32 width1  =  ((second + 256) * 640) / 256;
        s32 height1  =  ((second + 256) * 480) / 256;

        s32 width2 = ((currentFrame * 8 % 60 + 256) * 640) / 256;
        s32 height2 = ((currentFrame * 8 % 60 + 256) * 480) / 256;

        JUtility::TColor matColor(255, 255, 255, (128 - second * 2) / 4);

        GXSetChanMatColor(GX_COLOR0A0, matColor);
        drawScreenQuad(-((width1 - 640) / 2), -((height1 - 480) / 2), width1, height1);

        matColor.a = (128 - mCurrentFrame * 8 % 60 * 2) / 4;

        GXSetChanMatColor(GX_COLOR0A0, matColor);
        drawScreenQuad(-((width2 - 640) / 2), -((height2 - 480) / 2), width2, height2);

        switch (mPhase) {
            case SCREEN_PHASE_IN:
                break;
            case SCREEN_PHASE_OUT:
                if (mCurrentFrame >= mLength) {
                    mCurrent = SCREEN_TRANSITION_NONE;
                }
                break;
        }
        break;
    }
    case SCREEN_TRANSITION_BLACK: {
        drawGraph1();
        defaultOrthoView();
        GXLoadTexObj(pScreenTexture, GX_TEXMAP0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_NONE);

        s32 width = (mCurrentFrame * 640) / mLength;
        s32 height = (mCurrentFrame * 480) / mLength;
        GXSetChanMatColor(GX_COLOR0A0, JUtility::TColor(255, 255, 255, 255));
        drawScreenQuad(320 - (width / 2),  240 - (height / 2), width, height);
        break;
    }
    case SCREEN_TRANSITION_NONE:
    case SCREEN_TRANSITION_BLACK_FADE:
    case SCREEN_TRANSITION_WHITE_FADE:
        break;
    }

    lbl_803A3820.fn_80008654();
}
