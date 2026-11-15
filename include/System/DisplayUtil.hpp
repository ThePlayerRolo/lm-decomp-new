#ifndef DISPLAY_UTIL_HPP
#define DISPLAY_UTIL_HPP

#include <types.h>
#include <dolphin/mtx.h>

void initDisplay();
void fn_80007800();
void changeFrameBuffer();
void defaultOrthoView();
void setViewportJitter(f32 left, f32 top, f32 width, f32 height, f32 near, f32 far);
void fn_800079B0();
void fn_80007E50(u16);
void setFrameRateDivisor(s32);
void fn_80007E70(bool);
void* getMainFrameBuffer();
void* getPrevMainFrameBuffer();
u32 getFrameRateDivisor();
void setIntRenderModeVFilter(u8 vfilterVal);

// Progressive mode related functions start
void fn_80007F28();
void fn_80007F90();
void fn_80008004();
void updateProgressiveMode();
// Progressive mode related functions end

extern Mtx sDefaultMtx;
extern void* lbl_803A3810; // Probably some struct
extern s32 lbl_804D8058; // Unsure of typing

#endif
