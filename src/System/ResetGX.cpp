#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>

#include "System/ResetGX.hpp"
#include "System/DisplayUtil.hpp"
#include "System/80008418.hpp"


GXColor sReset = {0, 0, 0, 0};
GXColor sWhite = {0xFF, 0xFF, 0xFF, 0xFF};
GXColor sBlack = {0, 0, 0, 0xFF};

void resetGXState() {
    setViewportJitter(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 0x280, 0x1E0);
    GXSetCurrentMtx(0);
    GXSetCullMode(GX_CULL_BACK);
    GXLoadPosMtxImm(lbl_803A3820._18C, 0);

    GXLoadPosMtxImm(sDefaultMtx, 3);
    GXLoadPosMtxImm(sDefaultMtx, 6);
    GXLoadPosMtxImm(sDefaultMtx, 9);
    GXLoadPosMtxImm(sDefaultMtx, 12);
    GXLoadPosMtxImm(sDefaultMtx, 15);
    GXLoadPosMtxImm(sDefaultMtx, 18);
    GXLoadPosMtxImm(sDefaultMtx, 21);
    GXLoadPosMtxImm(sDefaultMtx, 24);
    GXLoadPosMtxImm(sDefaultMtx, 27);

    GXLoadNrmMtxImm(lbl_803A3820._18C, 0);
    GXLoadNrmMtxImm(sDefaultMtx, 3);
    GXLoadNrmMtxImm(sDefaultMtx, 6);
    GXLoadNrmMtxImm(sDefaultMtx, 9);
    GXLoadNrmMtxImm(sDefaultMtx, 12);
    GXLoadNrmMtxImm(sDefaultMtx, 15);
    GXLoadNrmMtxImm(sDefaultMtx, 18);
    GXLoadNrmMtxImm(sDefaultMtx, 21);
    GXLoadNrmMtxImm(sDefaultMtx, 24);
    GXLoadNrmMtxImm(sDefaultMtx, 27);

    GXSetNumChans(1);

    GXSetChanAmbColor(GX_COLOR0A0, sBlack);
    GXSetChanMatColor(GX_COLOR0A0, sWhite);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);

    GXSetChanAmbColor(GX_COLOR1A1, sBlack);
    GXSetChanMatColor(GX_COLOR1A1, sWhite);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);

    GXLoadTexMtxImm(sDefaultMtx, 30, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 33, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 36, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 39, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 42, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 45, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 48, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 51, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 54, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 57, GX_MTX3x4);
    GXLoadTexMtxImm(sDefaultMtx, 60, GX_MTX3x4);

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXEnableTexOffsets(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXSetNumTevStages(1);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    
    GXSetTevKColor(GX_KCOLOR0, sWhite);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
    GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K0_A);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXSetDstAlpha(GX_FALSE, 255);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_FALSE);
    GXSetDither(GX_TRUE);
}

Vec gZeroVec = {0, 0, 0};

Mtx sDefaultMtx = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f}
};
