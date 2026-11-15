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

class JUTDirectPrint;

void initDisplay();
void beginFrame();
void endFrame();
void defaultOrthoView();
void setViewportJitter(f32, f32, f32, f32, f32, f32);
void applyRenderMode();
void setDisplayFlags(u16);
void setFrameRateDivisor(s32);
void setDoubleBuffered(bool);
void* getMainFrameBuffer();
void* getPrevMainFrameBuffer();
u32 getFrameRateDivisor();
void setIntRenderModeVFilter(s32);

// Progressive mode related functions start
void checkProgressiveScanPrompt();
void updateProgressiveScanPrompt();
void tickProgressiveMessage();
void applyProgressiveChoice();
// Progressive mode related functions end

extern ProgressiveScanState sProgressiveScanPromptState;
extern JUTDirectPrint* sDirectPrintManager;

#endif
