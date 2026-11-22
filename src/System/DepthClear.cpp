#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>

#include "System/DepthClear.hpp"
#include "System/80008418.hpp"
#include "System/DisplayUtil.hpp"


static u8 sClearDepthTex[0x40] ATTRIBUTE_ALIGN(32) = {
    0x00, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF,
    0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
};

void drawZTextureQuad(u16 x, u16 y, u16 width, u16 height) {
    GXTexObj gObj;

    GXInitTexObj(&gObj, sClearDepthTex, 4, 4, GX_TF_Z24X8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&gObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&gObj, GX_TEXMAP0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x, y, -900.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x + width, y, -900.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(x + width, y + height, -900.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(x, y + height, -900.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

void clearDepthRect(u16 x, u16 y, u16 width, u16 height) {
    defaultOrthoView();
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);

    drawZTextureQuad(x, y, width, height);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    lbl_803A3820.fn_80008654();
}
