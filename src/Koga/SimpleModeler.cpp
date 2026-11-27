#include "Koga/SimpleModeler.hpp"
#include "System/80008418.hpp"
#include "Unsorted/SimpleDraw.hpp"

dummy_float_data()

namespace Koga {
    void drawCylinder(const Vec& rTranslation, f32 width, f32 height, GXColor color) {
        FORCE_DONT_INLINE;

        Mtx objectMtx;
        Mtx translation;
        Mtx scale;
        Mtx rotation;

        MTXTrans(translation, rTranslation.x, rTranslation.y + height / 2.0f, rTranslation.z);
        MTXScale(scale, width, height / 2.0f, width);
        MTXRotRad(rotation, 'x', DEG_TO_RAD(90.0f));

        PSMTXConcat(lbl_803A3820._18C, translation, objectMtx);
        PSMTXConcat(objectMtx, scale, objectMtx);
        PSMTXConcat(objectMtx, rotation, objectMtx);
        GXLoadPosMtxImm(objectMtx, 0);
        GXSetCurrentMtx(0);
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
        for (SphereInfo* sphere = mSpheres.getArray(); sphere != mSpheres.getLastMember(); sphere++) {
            drawSimpleSphere(sphere->mSize, sphere->mTranslation, sphere->mColor, 1);
        }

        for (CylinderInfo* cylinder = mCylinders.getFirstMember(); cylinder != mCylinders.getMaxIter(); cylinder++) {
            drawCylinder(cylinder->mTranslation, cylinder->mWidth, cylinder->mHeight, cylinder->mColor);
        }

        for (CubeInfo* cube = mCubes.getFirstMember(); cube != mCubes.getMaxIter(); cube++) {
            Mtx cubeMtx;
            PSMTXCopy(cube->mMtx, cubeMtx);
            drawSimpleCube(cube->mMtx, cube->mColor);
        }

        mSpheres.resetSize();
        mCylinders.resetSize();
        mCubes.resetSize();
    }

    SimpleModeler* SimpleModeler::fn_800BB88C() {
        setInitialized();
        return this;
    }

    void SimpleModeler::setInitialized() {
        sSimpleModelerInitialized += 1;
    }
}
