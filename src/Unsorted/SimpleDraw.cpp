#include "Unsorted/SimpleDraw.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "Unsorted/80008418.hpp"

void fn_8005A550();  // some function related to initing gx settings
void fn_800952D8(Mtx mtx, Quaternion* rQuat);
void fn_800966E4(Mtx mtx, f32 scale);

void setSimpleTevSettings(GXColor tevColor, bool param_2) {
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

    if (tevColor.a == 255) {
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

    GXSetTevColor(GX_TEVREG0, tevColor);
}

void drawSimpleLine(const Vec& rPoint1, const Vec& rPoint2, u8 lineWidth, GXColor color) {
    setSimpleTevSettings(color, true);
    GXLoadPosMtxImm(lbl_803A3820._18C, 3);
    GXSetCurrentMtx(3);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, FALSE);
    GXSetLineWidth(lineWidth, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(rPoint1.x, rPoint1.y, rPoint1.z);
    GXPosition3f32(rPoint2.x, rPoint2.y, rPoint2.z);
}

void drawSimpleSphere(f32 size, const Vec& rTranslation, GXColor color, u32 depth) {
    Mtx sphereMtx;

    fn_8005A550();
    MTXScale(sphereMtx, size, size, size);
    sphereMtx[0][3] = rTranslation.x;
    sphereMtx[1][3] = rTranslation.y;
    sphereMtx[2][3] = rTranslation.z;
    PSMTXConcat(lbl_803A3820._18C, sphereMtx, sphereMtx);
    GXLoadPosMtxImm(sphereMtx, 3);
    GXSetCurrentMtx(3);
    setSimpleTevSettings(color, true);
    GXDrawSphere1(depth);
}

void drawSimpleCubeQuat(const Vec& rTranslation, const Vec& rScale, GXColor color, Quaternion* pQuat) {
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

    drawSimpleCube(objectMtx, color);
}

void drawSimpleCube(Mtx objectMtx, GXColor rColor) {
    Mtx cubeMtx;
    PSMTXCopy(objectMtx, cubeMtx);
    fn_800966E4(cubeMtx, 0.86602539f);
    PSMTXConcat(lbl_803A3820._18C, cubeMtx, cubeMtx);
    fn_8005A550();
    GXLoadPosMtxImm(cubeMtx, 3);
    GXSetCurrentMtx(3);
    setSimpleTevSettings(rColor, true);
    GXDrawCube();
}

void drawSimpleCylinder(const Vec& rTrans, f32 width, f32 height, GXColor color) {
    Mtx cylinderMtx;
    fn_8000A40C(width, width, height / 2.0f, rTrans.x, rTrans.y + height / 2.0f, rTrans.z, cylinderMtx, 0x4000, 0, 0);
    PSMTXConcat(lbl_803A3820._18C, cylinderMtx, cylinderMtx);
    fn_8005A550();
    GXLoadPosMtxImm(cylinderMtx, 3);
    GXSetCurrentMtx(3);
    setSimpleTevSettings(color, true);
    GXDrawCylinder(32);
}

// https://decomp.me/scratch/0122d
void drawSimpleDebugAxes(f32 distance, Mtx mtx) {
    GXColor red = {255, 0, 0, 255};
    GXColor green = {0, 255, 0, 255};
    GXColor blue = {0, 0, 255, 255};

    const Vec zeroVec = { 0.0f, 0.0f, 0.0f };

    Vec center;
    Vec zPosition;
    Vec yPosition;
    Vec xPosition;

    center = zeroVec;
    zPosition = zeroVec;
    yPosition = zeroVec;
    xPosition = zeroVec;

    f32 local_64 = mtx[0][0];
    f32 local_60 = mtx[1][0];
    f32 local_5c = mtx[2][0];
    f32 local_70 = mtx[0][1];
    f32 local_6c = mtx[1][1];
    f32 local_68 = mtx[2][1];
    f32 local_7c = mtx[0][2];
    f32 local_78 = mtx[1][2];
    f32 local_74 = mtx[2][2];
    f32 local_88 = mtx[0][3];
    f32 local_84 = mtx[1][3];
    f32 local_80 = mtx[2][3];

    center.x = local_88;
    center.y = local_84;
    center.z = local_80;

    zPosition.x = local_7c;
    zPosition.y = local_78;
    zPosition.z = local_74;
    yPosition.x = local_70;
    yPosition.y = local_6c;
    yPosition.z = local_68;
    xPosition.x = local_64;
    xPosition.y = local_60;
    xPosition.z = local_5c;

    PSVECScale(&xPosition, &xPosition, distance);
    PSVECAdd(&center, &xPosition, &xPosition);
    setSimpleTevSettings(red, true);
    GXLoadPosMtxImm(lbl_803A3820._18C, 3);
    GXSetCurrentMtx(3);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, FALSE);
    GXSetLineWidth(24, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(center.x, center.y, center.z);
    GXPosition3f32(xPosition.x, xPosition.y, xPosition.z);

    PSVECScale(&yPosition, &yPosition, distance);
    PSVECAdd(&center, &yPosition, &yPosition);
    setSimpleTevSettings(green, true);
    GXLoadPosMtxImm(lbl_803A3820._18C, 3);
    GXSetCurrentMtx(3);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, FALSE);
    GXSetLineWidth(24, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(center.x, center.y, center.z);
    GXPosition3f32(yPosition.x, yPosition.y, yPosition.z);

    PSVECScale(&zPosition, &zPosition, distance);
    PSVECAdd(&center, &zPosition, &zPosition);
    setSimpleTevSettings(blue, true);
    GXLoadPosMtxImm(lbl_803A3820._18C, 3);
    GXSetCurrentMtx(3);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, FALSE);
    GXSetLineWidth(24, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(center.x, center.y, center.z);
    GXPosition3f32(zPosition.x, zPosition.y, zPosition.z);
}
