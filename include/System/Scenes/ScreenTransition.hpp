#ifndef SCREEN_TRANSITION_HPP
#define SCREEN_TRANSITION_HPP

#include <dolphin/types.h>

#include "System/Scenes/J2DTexture_k.hpp"

// TODO Better names but SCREEN_TRANSITION_TYPE_* felt too long. Used by mPhase
#define SCREEN_PHASE_OUT 1
#define SCREEN_PHASE_IN 2
#define SCREEN_PHASE_DONE 3
#define SCREEN_PHASE_UNK 4

enum ScreenTransitionType {
    /* 0x0 */ SCREEN_TRANSITION_NONE,
    /* 0x1 */ SCREEN_TRANSITION_FADE,
    /* 0x2 */ SCREEN_TRANSITION_BLACK_FADE,
    /* 0x3 */ SCREEN_TRANSITION_WHITE_FADE,
    /* 0x4 */ SCREEN_TRANSITION_SIDEWIPE,
    /* 0x5 */ SCREEN_TRANSITION_ZOOM_ECHO, // Expands "ghost" copies of the screen to create shockwave looking blur
    /* 0x6 */ SCREEN_TRANSITION_IMAGE,
    /* 0x7 */ SCREEN_TRANSITION_BLACK, // Makes the screen fully black
};

class ScreenTransition {
public:
    ScreenTransition();
    ~ScreenTransition();

    void switchTransition(ScreenTransitionType, s16);
    void startTransitionIn();
    void setTransitionSettings();
    void switchToNextTransition();
    BOOL update();
    void drawScreenQuad(s32, s32, s32, s32);
    void drawScreen(GXTexObj*);
    inline void drawGraph1();
    inline void drawSideWipe();

    void draw(GXTexObj*);

    inline void fillInline();

    /* 0x000 */ ScreenTransitionType mCurrent;
    /* 0x004 */ ScreenTransitionType mNext;
    /* 0x008 */ s32 mPhase;
    /* 0x00C */ s32 mCurrentFrame;
    /* 0x010 */ s32 _10;
    /* 0x014 */ J2DTexture_k mTexture;
    /* 0x190 */ u16 _190;
    /* 0x192 */ GXColor mColor; // TODO: Is probably JUTColor, but the constructors weird
    /* 0x196 */ s16 mLength;
    /* 0x198 */ s16 mDelayFrames;
};

#endif
