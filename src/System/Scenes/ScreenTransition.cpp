#include "System/Scenes/ScreenTransition.hpp"
#include "Unsorted/80008418.hpp"
#include "Unsorted/LMDisplayUtil.hpp"
#include <JSystem/J2D/J2DOrthoGraph.hpp>
#include <JSystem/JUtility/JUTColor.hpp>
#include <JSystem/JUtility/JUTTexture.hpp>
#include <dolphin/gx.h>

dummy_float_data();

static ScreenTransition sUnusedScreenTransition; // seems to be unused in the final game

ScreenTransition::ScreenTransition() : mTexture() {
    mCurrent = SCREEN_TRANSITION_NONE;
    mNext = SCREEN_TRANSITION_NONE;
    _8 = 0;
    mCurrentFrame = 0;
    _10 = 0;
    _190 = 0;
    mColor.r = 0;
    mColor.g = 0;
    mColor.b = 0;
    mColor.a = 255;
    mLength = 30;
    _198 = 0;
}

ScreenTransition::~ScreenTransition() { }

void ScreenTransition::switchTransition(ScreenTransitionType nextTransition, s16 length) {
    _8 = 1;

    mNext = (nextTransition > SCREEN_TRANSITION_WHITE_FADE) ? SCREEN_TRANSITION_FADE : nextTransition;

    mCurrentFrame = 0;
    mLength = length;
    setTransitionSettings();
    switchToNextTransition();
    _198 = 0;
}

void ScreenTransition::fn_80039628() {
    _8 = 2;

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
        case SCREEN_TRANSITION_5:
        case SCREEN_TRANSITION_FADE:
            mCurrentFrame = mLength;
            break;
        default:
            mCurrentFrame = 255;
    }

    _198 = 3;
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

// https://decomp.me/scratch/AABHI
bool ScreenTransition::fn_80039770() {
    if (_198 > 0) {
        _198--;
        return false;
    }

    switch (mCurrent) {
        case SCREEN_TRANSITION_FADE:
            switch (_8) {
                case 1:
                    mCurrentFrame += LMGetVIMessageQueueUnk4();
                    if (mCurrentFrame >= mLength) {
                        mCurrentFrame = mLength;
                        _8 = 3;
                        return true;
                    }
                    break;
                case 2:
                    mCurrentFrame -= LMGetVIMessageQueueUnk4();

                    if (mCurrentFrame <= 0) {
                        mCurrentFrame = 0;
                        mCurrent = SCREEN_TRANSITION_NONE;
                        return true;
                    }
                    break;
            }
            break;
        case SCREEN_TRANSITION_SIDEWIPE:
            switch (_8) {
                case 1:
                    mCurrentFrame += LMGetVIMessageQueueUnk4();
                    if (mCurrentFrame >= mLength) {
                        mCurrentFrame = mLength;
                        _8 = 3;
                    }
                    return true;
                case 2:
                    mCurrentFrame += LMGetVIMessageQueueUnk4();

                    if (mCurrentFrame > mLength) {
                        mCurrentFrame = mLength;
                        mCurrent = SCREEN_TRANSITION_NONE;
                    }
                    return true;
            }
            break;
        case SCREEN_TRANSITION_5:
            switch (_8) {
                case 1:
                    mCurrentFrame += LMGetVIMessageQueueUnk4();
                    if (mCurrentFrame > mLength) {
                        mCurrentFrame = mLength;
                        _8 = 3;
                    }
                    return true;
                case 2:
                    mCurrentFrame -= LMGetVIMessageQueueUnk4();

                    if (mCurrentFrame < 1) {
                        mCurrentFrame = 0;
                        mCurrent = SCREEN_TRANSITION_NONE;
                    }
                    return true;
            }
            break;
        case SCREEN_TRANSITION_6:
            switch (_8) {
                case 1:
                    mCurrentFrame++;
                    if (mCurrentFrame > 1) {
                        _8 = 3;
                    }
                    return true;
                case 2:
                    mCurrentFrame -= LMGetVIMessageQueueUnk4() * 10;

                    if (mCurrentFrame < 1) {
                        mCurrentFrame = 0;
                        mCurrent = SCREEN_TRANSITION_NONE;
                    }
                    return true;
                case 3:
                    mCurrentFrame = 255;
                    break;
            }
            break;
        case SCREEN_TRANSITION_BLACK:
            switch (_8) {
                case 1:
                    mCurrentFrame -= LMGetVIMessageQueueUnk4();

                    if (mCurrentFrame < 1) {
                        mCurrentFrame = 0;
                        mCurrent = SCREEN_TRANSITION_NONE;
                    }
                    return true;
                case 2:
                    mCurrentFrame += LMGetVIMessageQueueUnk4();
                    if (mCurrentFrame > mLength) {
                        mCurrentFrame = mLength;
                        _8 = 3;
                    }
                    return true;
            }
        case SCREEN_TRANSITION_NONE:
        case SCREEN_TRANSITION_BLACK_FADE:
        case SCREEN_TRANSITION_WHITE_FADE:
            break;
    }

    return false;
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

    LMDefaultOrthoView();
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

    if (_8 == 1) {
        J2DFillBox(0, 0, (mCurrentFrame * 640) / mLength, 480, JUtility::TColor(mColor.r, mColor.g, mColor.b, 255));
    } else {
        J2DFillBox((mCurrentFrame * 640) / mLength, 0, 640, 480, JUtility::TColor(mColor.r, mColor.g, mColor.b, 255));
    }
}

// https://decomp.me/scratch/0eced
void ScreenTransition::draw(GXTexObj* pScreenTexture) {
    LMDefaultOrthoView();
    switch (mCurrent) {
    case SCREEN_TRANSITION_FADE:
        if (_8 == 1) {
            drawScreen(pScreenTexture);
        }

        drawGraph1();

        switch (_8) {
            case 1:
                if (mCurrentFrame >= 255) {
                    mCurrent = SCREEN_TRANSITION_NONE;
                }
                break;
            case 2:
                break;
        }
        break;
    case SCREEN_TRANSITION_SIDEWIPE:
        drawSideWipe();
        break;
    case SCREEN_TRANSITION_6:
        switch (_8) {
            case 1:
                break;
            case 3:
                mTexture.draw_8003B0E8(0, 0, mTexture.mTextures[0]->getWidth(), mTexture.mTextures[0]->getHeight());
                break;
            case 4:
                break;
            case 2:
                GXSetChanMatColor(GX_COLOR0A0, JUtility::TColor(255, 255, 255, mCurrentFrame));
                mTexture.draw_8003B0E8(0, 0, 640, 480);
                break;
        };
        break;
    case SCREEN_TRANSITION_5:
        drawGraph1();
        LMDefaultOrthoView();
        GXLoadTexObj(pScreenTexture, GX_TEXMAP0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_NONE);

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

        switch (_8) {
            case 2:
                break;
            case 1:
                if (mCurrentFrame >= mLength) {
                    mCurrent = SCREEN_TRANSITION_NONE;
                }
                break;
        }
        break;
    case SCREEN_TRANSITION_BLACK:
        drawGraph1();
        LMDefaultOrthoView();
        GXLoadTexObj(pScreenTexture, GX_TEXMAP0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_NONE);

        s32 width = (mCurrentFrame * 480) / mLength;
        s32 height = (mCurrentFrame * 640) / mLength;
        GXSetChanMatColor(GX_COLOR0A0, JUtility::TColor(255, 255, 255, 255));
        drawScreenQuad(320 - (width / 2),  240 - (height / 2), width, height);
        break;
    case SCREEN_TRANSITION_NONE:
    case SCREEN_TRANSITION_BLACK_FADE:
    case SCREEN_TRANSITION_WHITE_FADE:
        break;
    }

    fn_80008654(&lbl_803A3820);
}
