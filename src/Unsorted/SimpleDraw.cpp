#include "Unsorted/SimpleDraw.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "Unsorted/80008418.hpp"

void fn_8005A550(); // some function related to initing gx settings
void fn_800952D8(Mtx mtx, Quaternion* rQuat);
void fn_800966E4(Mtx mtx, f32 scale);

void setSimpleTevSettings(const GXColor& rTevColor, bool param_2) {
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, TRUE, GX_TEVPREV);

    if (rTevColor.a == 255) {
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
        GXSetZMode(TRUE, GX_LESS, TRUE);
    } else {
        if (param_2) {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_SET);
        } else {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        }
        GXSetZMode(TRUE, GX_LESS, FALSE);
    }

    GXSetTevColor(GX_TEVREG0, rTevColor);
}

// https://decomp.me/scratch/kFc84
void drawSimpleLine(const Vec& rPoint1, const Vec& rPoint2, u8 lineWidth, const GXColor& rColor) {
    GXColor color;
    color = rColor;

    setSimpleTevSettings(color, true);
    GXLoadPosMtxImm(lbl_803A3820._18C, 3);
    GXSetCurrentMtx(3);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetLineWidth(lineWidth, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(rPoint1.x, rPoint1.y, rPoint1.z);
    GXPosition3f32(rPoint2.x, rPoint2.y, rPoint2.z);
}

void drawSimpleSphere(f32 size, const Vec& rTranslation, const GXColor& rColor, u32 depth) {
    Mtx sphereMtx;

    fn_8005A550();
    MTXScale(sphereMtx, size, size, size);
    sphereMtx[0][3] = rTranslation.x;
    sphereMtx[1][3] = rTranslation.y;
    sphereMtx[2][3] = rTranslation.z;
    PSMTXConcat(lbl_803A3820._18C, sphereMtx, sphereMtx);
    GXLoadPosMtxImm(sphereMtx, 3);
    GXSetCurrentMtx(3);
    GXColor color = rColor;
    setSimpleTevSettings(color, true);
    GXDrawSphere1(depth);
}

void drawSimpleCubeQuat(const Vec& rTranslation, const Vec& rScale, const GXColor& rColor, Quaternion* pQuat) {
    Mtx objectMtx;
    Mtx quatMtx;

    MTXScale(objectMtx, rScale.x, rScale.y, rScale.z);
    objectMtx[0][3] = rTranslation.x;
    objectMtx[1][3] = rTranslation.y;
    objectMtx[2][3] = rTranslation.z;

    if (pQuat != nullptr) {
        fn_800952D8(quatMtx, pQuat);
        PSMTXConcat(quatMtx, objectMtx, objectMtx);
    }

    GXColor color = rColor;
    drawSimpleCube(objectMtx, color);
}


void drawSimpleCube(Mtx objectMtx, const GXColor& rColor) {
    Mtx cubeMtx;
    PSMTXCopy(objectMtx, cubeMtx);
    fn_800966E4(cubeMtx, 0.86602539f);
    PSMTXConcat(lbl_803A3820._18C, cubeMtx, cubeMtx);
    fn_8005A550();
    GXLoadPosMtxImm(cubeMtx, 3);
    GXSetCurrentMtx(3);
    GXColor color = rColor;
    setSimpleTevSettings(color, true);
    GXDrawCube();
}

void drawSimpleCylinder(const Vec& rTrans, f32 width, f32 height, const GXColor& rColor) {
    Mtx cylinderMtx;
    fn_8000A40C(width, width, height * 0.5f, rTrans.x, rTrans.y + height * 0.5f, rTrans.z, cylinderMtx, 0x4000, 0, 0);
    PSMTXConcat(lbl_803A3820._18C, cylinderMtx, cylinderMtx);
    fn_8005A550();
    GXLoadPosMtxImm(cylinderMtx, 3);
    GXSetCurrentMtx(3);
    GXColor color = rColor;
    setSimpleTevSettings(color, true);
    GXDrawCylinder(32);
}
