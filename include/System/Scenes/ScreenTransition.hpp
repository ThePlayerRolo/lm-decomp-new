#pragma once

#include "System/Scenes/J2DTexture_k.hpp"

enum ScreenTransitionType {
    /* 0x0 */ SCREEN_TRANSITION_NONE,
    /* 0x1 */ SCREEN_TRANSITION_FADE,
    /* 0x2 */ SCREEN_TRANSITION_BLACK_FADE,
    /* 0x3 */ SCREEN_TRANSITION_WHITE_FADE,
    /* 0x4 */ SCREEN_TRANSITION_SIDEWIPE,
    /* 0x5 */ SCREEN_TRANSITION_5, // Has a screen buffer of the mansion after an afterimage?
    /* 0x6 */ SCREEN_TRANSITION_6,
    /* 0x7 */ SCREEN_TRANSITION_BLACK, // Makes the screen fully black
};

class ScreenTransition {
public:
    ScreenTransition();

    ~ScreenTransition();

    void switchTransition(ScreenTransitionType, s16);
    void fn_80039628();
    void setTransitionSettings();
    void switchToNextTransition();
    bool fn_80039770();
    void drawScreenQuad(s32 x, s32 y, s32 w, s32 h);
    void drawScreen(GXTexObj* pScreenObj);
    inline void drawGraph1();
    inline void drawSideWipe();

    void draw(GXTexObj* pScreenObj);

    inline void fillInline();

    /* 0x000 */ ScreenTransitionType mCurrent;
    /* 0x004 */ ScreenTransitionType mNext;
    /* 0x008 */ s32 _8;
    /* 0x00C */ s32 mCurrentFrame;
    /* 0x010 */ s32 _10;
    /* 0x014 */ J2DTexture_k mTexture;
    /* 0x190 */ u16 _190;
    /* 0x192 */ GXColor mColor; // TODO: Is probably JUTColor, but the constructors weird
    /* 0x196 */ s16 mLength;
    /* 0x198 */ s16 _198;
};
