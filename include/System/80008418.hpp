#ifndef _80008418_HPP
#define _80008418_HPP

#include <dolphin/mtx.h>
#include <types.h>

// Should validate this class, as well as return types/args of functions.
class unk_lbl_803A3820 {
public:
    void fn_8000853C();
    void fn_8000858C();
    void fn_800085D8();
    void fn_80008654();
    void fn_800087D0();

    void fn_80008928(); //Could be a static since lbl_803A3820 is passed at the end rather than r3
    void fn_800089DC(); //Could also be static
    void fn_80008AA8();
    void fn_80008D58(); //Could also be static
    void fn_80009148();
    bool fn_800093EC();
    void fn_80009490(); //Could be static

    /* 0x000 */ u8 pad[0x18C];
    /* 0x18C */ Mtx _18C;
    /* 0x1BC */ u8 pad2[0x260 - 0x1BC];

private:
    void fn_80008418(void*); // Unknown second arg, src only defined.
};

extern unk_lbl_803A3820 lbl_803A3820;

#endif
