#ifndef SA_GRAIN_CONTROL
#define SA_GRAIN_CONTROL

#include "dolphin/types.h"

template <typename T>
struct saGrainList {
    void init() {
        mHead = &mSentinel;
        mHead->mNext = mHead;
        mHead->mPrev = mHead;
    }

    T mSentinel;
    T* mHead;
};


template<typename Control, typename Param>
class saGrainControl {
public:
    void init(u16 paramCount, u16 controlCount);


    /* 0x00 */ Control* mControls;
    /* 0x04 */ Param* mParams;
    /* 0x08 */ saGrainList<Param> mFreeParam;
    saGrainList<Control> mControlList;
    saGrainList<Control> mControlList2;
};

#pragma opt_unroll_loops off // idk why i need to remove this optimization, maybe when something else will be decompiled
template<typename Control, typename Param>
void saGrainControl<Control, Param>::init(u16 paramCount, u16 controlCount) {
    Param* param = mParams;
    Control* control = mControls;
    Param* nextParam = param + 1;
    Control* nextControl = control + 1;

    mControlList2.init();
    
    mControlList.mHead = &mControlList.mSentinel;
    mControlList.mHead->mNext = control;
    control->mPrev = mControlList.mHead;
    for (u16 i = 0; i < controlCount; i++) {
        control->mParams.init();
        control++;
    }

    control = mControls;
    for (u8 i = 0; i < controlCount - 1; i++) {
        control->mNext = nextControl;
        nextControl->mPrev = control;
        control++;
        nextControl++;
    }
    control->mNext = mControlList.mHead;
    mControlList.mHead->mPrev = control;

    mFreeParam.mHead = &mFreeParam.mSentinel;
    mFreeParam.mHead->mNext = param;
    param->mPrev = mFreeParam.mHead;
    for (u16 i = 0; i < paramCount - 1; i++) {
        param->mNext = nextParam;
        nextParam->mPrev = param;
        param++;
        nextParam++;
    }
    param->mNext = mFreeParam.mHead;
    mFreeParam.mHead->mPrev = param;
}

#endif
