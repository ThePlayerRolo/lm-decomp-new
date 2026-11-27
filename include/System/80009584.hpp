#ifndef _80009584_HPP
#define _80009584_HPP

#include <JSystem/JUtility/JUTGamePad.hpp>

#include <dolphin/mtx.h>
#include <types.h>

void setDirectionalRepeat(s32);
void fn_80009580();
f32 distance(Vec*, Vec*);

extern JUTGamePad* sGamePad;

#endif
