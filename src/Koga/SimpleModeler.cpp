#include "Koga/SimpleModeler.hpp"
#include "Unsorted/80008418.hpp"
#include "Unsorted/SimpleDraw.hpp"

dummy_float_data()

namespace Koga {
    // float reg swap https://decomp.me/scratch/uPCzj
    void drawCylinder(const Vec& rTranslation, f32 width, f32 height, const GXColor& rColor) {
        FORCE_DONT_INLINE;

        Mtx objectMtx;
        Mtx translation;
        Mtx scale;
        Mtx rotation;

        MTXTrans(translation, rTranslation.x, rTranslation.y + height * 0.5f, rTranslation.z);
        MTXScale(scale, width, height * 0.5f, width);
        MTXRotRad(rotation, 'x', DEG_TO_RAD(90.0f));

        PSMTXConcat(lbl_803A3820._18C, translation, objectMtx);
        PSMTXConcat(objectMtx, scale, objectMtx);
        PSMTXConcat(objectMtx, rotation, objectMtx);
        GXLoadPosMtxImm(objectMtx, 0);
        GXSetCurrentMtx(0);
        GXColor color = rColor;
        setSimpleTevSettings(color, true);
        GXDrawCylinder(32);
    }

    //https://decomp.me/scratch/kmGpk
    void SimpleModeler::newSimpleModeler() {
        if (sSimpleModelerInitialized == 0) {
            //fn_800BB88C(); Something funky here, maybe its a part of inline constructor of SimpleModeler? Maybe has a base class?
            sCurSimpleModeler = new SimpleModeler();
        }
    }

    void SimpleModeler::deleteSimpleModeler() {
        if (sSimpleModelerInitialized == 1) {
            delete sCurSimpleModeler;
        }
    }

    bool SimpleModeler::addCylinder(const Vec& rTranslation, f32 width, f32 height, const GXColor& rColor) {
        if (mCylinders.getSize() >= 32) {
            return false;
        }

        CylinderInfo cylinder;
        cylinder.mTranslation = rTranslation;
        cylinder.mWidth = width;
        cylinder.mHeight = height;
        cylinder.mColor = rColor;
        mCylinders.addMember(&cylinder);
        return true;
    }

    bool SimpleModeler::addCube(Mtx mtx, const GXColor& rColor) {
        if (mCubes.getSize() >= 32) {
            return true;  // bug?
        }

        CubeInfo cube;
        PSMTXCopy(cube.mMtx, mtx);
        cube.mColor = rColor;
        mCubes.addMember(&cube);
        return true;
    }

    void SimpleModeler::draw() {
        for (SphereInfo* sphere = mSpheres.getFirstMember(); sphere != mSpheres.getMaxIter(); sphere++) {
            GXColor color = sphere->mColor;
            drawSimpleSphere(sphere->mSize, sphere->mTranslation, color, 1);
        }

        for (CylinderInfo* cylinder = mCylinders.getFirstMember(); cylinder != mCylinders.getMaxIter(); cylinder++) {
            GXColor color = cylinder->mColor;
            drawCylinder(cylinder->mTranslation, cylinder->mWidth, cylinder->mHeight, color);
        }

        for (CubeInfo* cube = mCubes.getFirstMember(); cube != mCubes.getMaxIter(); cube++) {
            Mtx cubeMtx;
            PSMTXCopy(cube->mMtx, cubeMtx);
            GXColor color = cube->mColor;

            drawSimpleCube(cube->mMtx, color);
        }

        mSpheres.resetSize();
        mCylinders.resetSize();
        mCubes.resetSize();
    }

    SimpleModeler* SimpleModeler::fn_800BB88C() {
        fn_800BB8BC();
        return this;
    }

    void SimpleModeler::fn_800BB8BC() {
        sSimpleModelerInitialized += 1;
    }
}
