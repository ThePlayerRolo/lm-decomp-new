#ifndef _8000AED8_HPP
#define _8000AED8_HPP

#include <types.h>


// Should validate what this struct is.
struct AED8Struct {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
    u32 _14;
};

// Unsure of return types / args. should validate these
void fn_8000AED8(AED8Struct*, u32);
void fn_8000AEF8(void*);
void fn_8000AFA8();
void fn_8000B014();
void fn_8000B228();

extern void* lbl_803A3A98;

#endif
