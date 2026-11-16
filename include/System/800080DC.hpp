#ifndef _800080DC_HPP
#define _800080DC_HPP

#include <types.h>

struct SomeOtherUnk {
    inline SomeOtherUnk() { 
        _0 = 0;
        _4 = 1; 
    }
    u32 _0;
    u32 _4;
    u32 _8;
};

// Unsure of return types/args
void fn_800080DC(SomeOtherUnk*);
void fn_8000812C(SomeOtherUnk*);
void fn_800081A8(SomeOtherUnk*);
void fn_80008394();
void fn_800083A4(u32);
void fn_800083B4(u32);

extern SomeOtherUnk lbl_803A3810;

#endif
