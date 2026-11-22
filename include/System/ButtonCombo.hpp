#ifndef BUTTON_COMBO_HPP
#define BUTTON_COMBO_HPP

#include <types.h>

// Should validate what this struct is.
class ButtonCombo {
    public:
        ButtonCombo(u32*);
        s32 update();
    private:
        /* 0x00 */ s64 mLastTick;
        /* 0x08 */ u32 _8;
        /* 0x0C */ u32* mButtonSequence;
        /* 0x10 */ u32 mIndex;
        /* 0x14 */ BOOL mIsActive;
};

extern void* lbl_803A3A98;

#endif
