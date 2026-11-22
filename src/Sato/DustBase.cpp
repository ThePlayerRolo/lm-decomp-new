#include "Sato/DustBase.hpp"

void DustBase::init(u16 dustUnk1Count, u16 dustUnk2Count) {
    DustUnk1* dustUnk1 = mDustUnk1;
    DustUnk2* dustUnk2 = mDustUnk2;
    DustUnk1* nextUnk1 = dustUnk1 + 1;
    DustUnk2* nextUnk2 = dustUnk2 + 1;

    _220.init();

    _064.mHead = &_064.mSentinel;
    _064.mHead->mNext = dustUnk2;
    dustUnk2->mPrev = _064.mHead;
    for (u16 i = 0; i < dustUnk2Count; i++) {
        dustUnk2[i].mDustUnk1List.init();
        fn_8012B308(&dustUnk2[i]);
    }

    dustUnk2 = mDustUnk2;
    for (u8 i = 0; i < dustUnk2Count - 1; i++) {
        dustUnk2->mNext = nextUnk2;
        nextUnk2->mPrev = dustUnk2;
        dustUnk2++;
        nextUnk2++;
    }
    dustUnk2->mNext = _064.mHead;
    _064.mHead->mPrev = dustUnk2;

    _00c.mHead = &_00c.mSentinel;
    _00c.mHead->mNext = dustUnk1;
    dustUnk1->mPrev = _00c.mHead;
    for (u16 i = 0; i < dustUnk1Count - 1; i++) {
        dustUnk1->mNext = nextUnk1;
        nextUnk1->mPrev = dustUnk1;
        dustUnk1++;
        nextUnk1++;
    }
    dustUnk1->mNext = _00c.mHead;
    _00c.mHead->mPrev = dustUnk1;
}

void DustBase::fn_8012B308(DustUnk2* dustUnk2) {
    dustUnk2->_2E = 0;
}
