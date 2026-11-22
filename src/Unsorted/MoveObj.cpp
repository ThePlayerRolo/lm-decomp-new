#include "Unsorted/MoveObj.hpp"
#include "Unsorted/AssortedEnManager.hpp"
#include "Unsorted/character.hpp"
#include "dolphin/mtx.h"
#include "macros.h"
#include "Unsorted/ActorData.hpp"
#include "Unsorted/s3dmodel.hpp"

dummy_float_data();
enemies_float_data();

s32 fn_8006A4E8(s32, const char*);
void fn_8013DCD8(Vec*, Vec*, Vec*, s32);

MoveObj::MoveObj() {
    _788 = 0;
}

MoveObj::~MoveObj() {
    delete mModel;
}

void MoveObj::fn_80067C30(const Vec* vec) {
    _6C = *vec;
    _68 = VECMag(&_6C);
    _78 = _6C;

    if (_68 > 0.000001f) {
        PSVECNormalize(&_78, &_78);
    }
}

void MoveObj::fn_80067CB0(f32 var1, f32 var2, f32 var3) {
    _44.set(var1, var2, var3);
    _5C = _44;
    _50 = _5C;

    _B4 = fn_80017ADC(_44, 0);
}

u16 MoveObj::fn_80067D3C(u16 val) {
    return ActorData::checkFlags(_3C, val);
}

bool MoveObj::fn_800681E8(const char* name) {
    s32 index = fn_8006A4E8(_3C, name);

    if (index == -1) {
        return false;
    }

    fn_80068238(index);

    return true;
}

void MoveObj::fn_80068238(s32 index) {
    if (_C4 != index) {
        _C4 = index;
        fn_80067F84();
    }
}

void MoveObj::fn_80068268(s32 val, JGeometry::TVec3<f32>& vec) {
    if ((_40 & 0x80000) != 0) {
        return;
    }

    _100 = vec;

    if (mModel != nullptr) {
        _40 |= 0x80000;
        fn_8013DCD8(_10C, _100, _44, val);
    }
}

void MoveObj::vt_0C(u16 x, u16 y, u16 z) {
    _86 = x;
    _84 = x;
    _8A = y;
    _88 = y;
    _8E = z;
    _8C = z;
}
