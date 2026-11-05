#ifndef YAY0_HPP
#define YAY0_HPP

#include <types.h>

struct Yay0Header {
    /* 0x00 */ u32 mMagic;
    /* 0x04 */ u32 mSize;
    /* 0x08 */ u32 mLinkOffset;
    /* 0x0C */ u32 mDataOffset;
};
    
s32 getYay0ArcSize(const u8*);
void decompressYay0(const u8*, u8*);

#endif
