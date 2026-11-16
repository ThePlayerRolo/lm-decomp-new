#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include "dolphin/mtx.h"
#include "math.h"
#include <types.h>

extern u32 lbl_80218210[2][4];
extern f32 lbl_80218230[];
extern f32 sinTable[1024];
extern f32 cosTable[4096];
extern u16 atanTable[1025];

void randomReset();
u32 randomInt();
u16 atan2BAM(f32 firstAxis, f32 secondAxis);
Vec lineIntersectWithPlane(Vec* f2, Vec* f3, Vec* f4, Vec* f5);
s32 getClosestPointOnLine(Vec* f1, Vec* f2, Vec* f3, f32* f4, Vec* f5);

#endif
