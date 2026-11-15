#ifndef _800098B0_HPP
#define _800098B0_HPP

#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>

extern GXColor sReset;
extern GXColor sWhite;
extern GXColor sBlack;

extern Mtx sDefaultMtx;
/* Move to C++ file when made
Mtx sDefaultMtx = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f}
};
*/

void fn_80009B80();

#endif
