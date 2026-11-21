#ifndef SIMPLE_MODELER_H_
#define SIMPLE_MODELER_H_

#include "MR/Array.hpp"
#include <dolphin/gx.h>
#include <JSystem/JGeometry/JGVec3.hpp>

namespace Koga {
    class SimpleModeler {
    public:
        struct SphereInfo {
            /* 0x00 */ Vec mTranslation;
            /* 0x0C */ f32 mSize;
            /* 0x10 */ GXColor mColor;
        };

        struct CylinderInfo {
            /* 0x00 */ Vec mTranslation;
            /* 0x0C */ f32 mWidth;
            /* 0x10 */ f32 mHeight;
            /* 0x14 */ GXColor mColor;
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

        bool addCylinder(const Vec& rTranslation, f32 param_2, f32 param_3, const GXColor& rTevColor);
        bool addCube(Mtx, const GXColor& rColor);

        void draw(); //Draws the models of each class in a loop.

        SimpleModeler* fn_800BB88C();
        void fn_800BB8BC();
    public:
        /* 0x004 */ MR::AssignableArray<SphereInfo, 32> mSpheres;
        /* 0x288 */ MR::AssignableArray<CylinderInfo, 32> mCylinders;
        /* 0x58C */ MR::AssignableArray<CubeInfo, 32> mCubes;

        static SimpleModeler* sCurSimpleModeler;
        static int sSimpleModelerInitialized;
    };

};

#endif
