#include "System/Scenes/J2DTexture_k.hpp"
#include <dolphin/gx.h>

J2DTexture_k::J2DTexture_k(JUTTexture* pTexture) : J2DPicture(pTexture), mTextureObj(mTextures[0]->getTexObj()) {
}

void J2DTexture_k::draw_8003AFEC(s32 x, s32 y, s32 w, s32 h, u32 color1, u32 color2, u32 color3, u32 color4) {
    s32 pointRight = x + w;
    s32 pointBottom = y + h;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3s16(x, y, 0);
    GXColor1u32(color1);
    GXTexCoord2u16( 0x0000, 0x0000);

    GXPosition3s16(pointRight, y, 0);
    GXColor1u32(color2);

    GXTexCoord2u16( 0x8000, 0x0000);

    GXPosition3s16(pointRight, pointBottom, 0);
    GXColor1u32(color3);
    GXTexCoord2u16( 0x8000, 0x8000);

    GXPosition3s16(x, pointBottom, 0);
    GXColor1u32(color4);
    GXTexCoord2u16(0x0000, 0x8000);

    GXEnd();
}

void J2DTexture_k::draw_8003B0E8(s32 x, s32 y, s32 h, s32 w) {
    s32 pointRight = x + h;
    s32 pointBottom = y + w;

    if (isValidTexture(0)) {
        mTextures[0]->load(GX_TEXMAP0);
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetNumTexGens(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3s16(x, y, 0);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x0000, 0x0000);

    GXPosition3s16(pointRight, y, 0);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x8000, 0x0000);

    GXPosition3s16(pointRight, pointBottom, 0);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x8000, 0x8000);

    GXPosition3s16(x, pointBottom, 0);
    GXColor1u32(0xFFFFFFFF); // white
    GXTexCoord2u16(0x0000, 0x8000);

    GXEnd();
}

void J2DTexture_k::draw_8003B264(s32 x, s32 y, s32 h, s32 w) {
    draw_8003B0E8(x - (h / 2), y - (w / 2), h, w);
}

void J2DTexture_k::draw_8003B29C(s32 x, s32 y, s32 w, s32 h,
    s32 texCoordLeft, s32 texCoordRight, s32 texCoordTop, s32 texCoordBottom, u32 color1, u32 color2, u32 color3, u32 color4)
{
    s32 pointRight = x + w;
    s32 pointBottom = y + h;
    s32 textureWidth = mTextures[0]->getWidth();
    s32 textureHeight = mTextures[0]->getHeight();

    if (isValidTexture(0)) {
        mTextures[0]->load(GX_TEXMAP0);
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetNumTexGens(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_VTX, 1, GX_DF_CLAMP, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    s32 topTexCoord = (texCoordTop * 32768) / textureHeight;
    s32 rightTexCoord = (texCoordRight * 32768) / textureWidth;
    s32 leftTexCoord = (texCoordLeft * 32768) / textureWidth;
    s32 bottomTexCoord = (texCoordBottom * 32768) / textureHeight;

    GXPosition3s16(x, y, 0);
    GXColor1u32(color1); // white
    GXTexCoord2u16(leftTexCoord, topTexCoord);

    GXPosition3s16(pointRight, y, 0);
    GXColor1u32(color2); // white
    GXTexCoord2u16(rightTexCoord, topTexCoord);

    GXPosition3s16(pointRight, pointBottom, 0);
    GXColor1u32(color3); // white
    GXTexCoord2u16(rightTexCoord, bottomTexCoord);

    GXPosition3s16(x, pointBottom, 0);
    GXColor1u32(color4); // white
    GXTexCoord2u16(leftTexCoord, bottomTexCoord);

    GXEnd();
}

void J2DTexture_k::draw_8003B43C(s32 x, s32 y, s32 w, s32 h, u32 color1, u32 color2, u32 color3, u32 color4) {
    if (isValidTexture(0)) {
        mTextures[0]->load(GX_TEXMAP0);
    }

    GXSetNumTexGens(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_VTX, 1, GX_DF_CLAMP, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

    draw_8003AFEC(x, y, w, h, color1, color2, color3, color4);
}
