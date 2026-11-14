#include "Unsorted/s3dmodel.hpp"
#include "JSystem/JKernel/JKRHeap.hpp"
#include <dolphin/os.h>

S3DModel::S3DModel(Info* param_1, s32 param_2) {
    init(param_1, param_2);
}

void S3DModel::init(Info* param_1, s32 param_2) {
    _0 = 0;
    _4 = param_1;

    s32 iVar1;
    if (_4 != nullptr) {
        iVar1 =  _4->_8 + _4->_C;
    } else {
        iVar1 = param_2;
    }

    if (param_2 != 0 && param_2 > iVar1) {
        OSErrorLine(119, "");
    }

    s32 sizeBase1 = (param_2 * 4);
    sizeBase1 *= 48;

    void* ppVar2 = JKRAllocFromHeap(nullptr, sizeBase1 + (sizeBase1 * 12), 4);

    if (ppVar2 == nullptr) {
        OSErrorLine(130, "");
    }

    _14 = ppVar2;
}


S3DModel::~S3DModel() {
    delete _14;
}
