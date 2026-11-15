#ifndef DISPLAY_UTIL_HPP
#define DISPLAY_UTIL_HPP

#include <types.h>
#include <dolphin/mtx.h>

struct DisplayState {
    /* 0x0 */ u16 mFlags;
    /* 0x2 */ bool mIsDoubleBuffered;
    /* 0x3 */ u8 mBufferIndex;
};

enum ProgressiveScanState {
    PSCAN_OFF,
    PSCAN_ASKING,
    PSCAN_SHOW_RESULT,
};

void initDisplay();
void fn_80007800();
void changeFrameBuffer();
void defaultOrthoView();
void setViewportJitter(f32 left, f32 top, f32 width, f32 height, f32 near, f32 far);
void applyRenderMode();
void setDisplayFlags(u16);
void setFrameRateDivisor(s32);
void setDoubleBuffered(bool);
void* getMainFrameBuffer();
void* getPrevMainFrameBuffer();
u32 getFrameRateDivisor();
void setIntRenderModeVFilter(u8 vfilterVal);

// Progressive mode related functions start
void checkProgressiveScanPrompt();
void updateProgressiveScanPrompt();
void tickProgressiveMessage();
void applyProgressiveChoice();
// Progressive mode related functions end

extern Mtx sDefaultMtx;
extern void* lbl_803A3810; // Probably some struct
extern ProgressiveScanState sProgressiveScanPromptState;

#endif
