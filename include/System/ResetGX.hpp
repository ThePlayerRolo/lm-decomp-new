#ifndef RESET_GX_HPP
#define RESET_GX_HPP

#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>

extern GXColor sReset;
extern GXColor sWhite;
extern GXColor sBlack;

extern Mtx sDefaultMtx;
extern Vec gZeroVec;

void resetGXState();

#endif
