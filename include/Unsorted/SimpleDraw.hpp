#ifndef SIMPLE_DRAW_HPP
#define SIMPLE_DRAW_HPP

#include <dolphin/mtx.h>
#include <dolphin/gx.h>

void setSimpleTevSettings(GXColor rTevColor, bool);
void drawSimpleLine(const Vec& rPoint1, const Vec& rPoint2, u8 lineWidth, GXColor color);
void drawSimpleSphere(f32 size, const Vec& rTranslation, GXColor rColor, u32 depth);
void drawSimpleCubeQuat(const Vec& rTranslation, const Vec& rScale, GXColor color, Quaternion* pQuat);
void drawSimpleCube(Mtx mtx, GXColor color);
void drawSimpleCylinder(const Vec& rTrans, f32 width, f32 height, GXColor color);
void drawSimpleDebugAxes(f32 distance, Mtx mtx);

#endif
