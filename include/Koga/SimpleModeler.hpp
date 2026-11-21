#ifndef SIMPLE_MODELER_H_
#define SIMPLE_MODELER_H_

#include "MR/Array.hpp"
#include <dolphin/gx.h>
#include <JSystem/JGeometry/JGVec3.hpp>

class unkSimpleModeler1 {
public:
    unkSimpleModeler1();
    ~unkSimpleModeler1();

    // TODO figure out what this data is
    /* 0x0 - 0x27C */ u8 _0[0x280];
    /* 0x280 */ s32 _280; //Some Counter or ptr?
};

namespace Koga {
    class SimpleModeler {
    public:
        struct CylinderInfo {
            /* 0x00 */ Vec _0;
            /* 0x0C */ f32 _C;
            /* 0x10 */ f32 _10;
            /* 0x14 */ GXColor mTevColor;
        };

        struct CubeInfo {
            /* 0x00 */ Mtx mMtx;
            /* 0x30 */ GXColor mColor;
        };

        SimpleModeler() {}

        //https://decomp.me/scratch/ILg4C
        /* 0x08 */ virtual ~SimpleModeler() {
            sSimpleModelerInitialized -= 1;
        }

        static void newSimpleModeler();
        static void deleteSimpleModeler();
        static SimpleModeler* getCurSimpleModeler() { return sCurSimpleModeler; }

        bool addCylinder(const Vec& param_1, f32 param_2, f32 param_3, const GXColor& rTevColor);

        bool addCube(Mtx, const GXColor& rColor); //Seems to be some Matrix copying or something similar of unkSimpleModeler3. Missing Args
        void draw(); //Draws the models of each class in a loop.

        SimpleModeler* fn_800BB88C();
        void fn_800BB8BC();
    public:
        /* 0x4 */ unkSimpleModeler1 mUnk1;
        /* 0x288 */ MR::AssignableArray<CylinderInfo, 32> mCylinders;
        /* 0x58C */ MR::AssignableArray<CubeInfo, 32> mCubes;

        static SimpleModeler* sCurSimpleModeler;
        static int sSimpleModelerInitialized;
    };

};

#endif
