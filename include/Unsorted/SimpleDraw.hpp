#ifndef SIMPLE_DRAW_HPP
#define SIMPLE_DRAW_HPP

#include <dolphin/mtx.h>
#include <dolphin/gx.h>

void setSimpleTevSettings(const GXColor& rTevColor, bool);
void drawSimpleLine(const Vec& rPoint1, const Vec& rPoint2, u8 lineWidth, const GXColor& rColor);
void drawSimpleSphere(f32 size, const Vec& rTranslation, const GXColor& rColor, u32 depth);
void drawSimpleCubeQuat(const Vec& rTranslation, const Vec& rScale, const GXColor& rColor, Quaternion* pQuat);
void drawSimpleCube(Mtx mtx, const GXColor& rColor);

#endif
