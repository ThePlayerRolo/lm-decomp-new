#include "Koga/SimpleModeler.hpp"

dummy_float_data()

namespace Koga {
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

    bool SimpleModeler::addCylinder(const Vec& param_1, f32 param_2, f32 param_3, const GXColor& rTevColor) {
        if (mCylinders.getSize() >= 32) {
            return false;
        }

        CylinderInfo cylinder;
        cylinder._0 = param_1;
        cylinder._C = param_2;
        cylinder._10 = param_3;
        cylinder.mTevColor = rTevColor;
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

    SimpleModeler* SimpleModeler::fn_800BB88C() {
        fn_800BB8BC();
        return this;
    }

    void SimpleModeler::fn_800BB8BC() {
        sSimpleModelerInitialized += 1;
    }
}


unkSimpleModeler1::unkSimpleModeler1() {
    _280 = 0; //Could also be nullptr
}
