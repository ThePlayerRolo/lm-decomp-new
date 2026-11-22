#ifndef DUST_BASE_HPP
#define DUST_BASE_HPP

#include "Sato/saGrainControl.hpp"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

struct Unk450 {
    /* 0x00 */ Vec* mPos;
};

struct DustUnk1 {
    /* 0x00 */ Vec _00;
    /* 0x0C */ Vec _0C;
    /* 0x18 */ Vec _18;
    /* 0x24 */ s16 _24;
    /* 0x26 */ u16 _26;
    /* 0x28 */ f32 _28;
    /* 0x2C */ f32 _2C;
    /* 0x30 */ f32 _30;
    /* 0x34 */ f32 _34;
    /* 0x38 */ f32 _38;
    /* 0x3C */ f32 _3C;
    /* 0x40 */ u8 _40;
    /* 0x44 */ s32 _44;
    /* 0x48 */ s32 _48;
    /* 0x4C */ DustUnk1* mNext;
    /* 0x50 */ DustUnk1* mPrev;
};

struct Unk98 {};

struct DustUnk2 {
    /* 0x000 */ u8 _000[0x0C];
    /* 0x00C */ Vec _0C;
    /* 0x018 */ Vec _18;
    /* 0x024 */ f32 _24;
    /* 0x028 */ f32 _28;
    /* 0x02C */ s16 _2C;
    /* 0x02E */ u8 _2E;
    /* 0x030 */ u32 _30;
    /* 0x034 */ u8 _034[0x38 - 0x34];
    /* 0x038 */ u32 _038;
    /* 0x03C */ u8 _3C;
    /* 0x03D */ bool _3D;
    /* 0x03E */ bool _3E;
    /* 0x040 */ saGrainList<DustUnk1> mDustUnk1List;
    /* 0x098 */ Unk98 _098;
    /* 0x140 */ DustUnk2* mNext;
    /* 0x144 */ DustUnk2* mPrev;
    /* 0x148 */ Unk450* _148;
    /* 0x14C */ void* _ptmf14c;
    /* 0x158 */ void* _ptmf158;
    /* 0x164 */ void* _ptmf164;
    /* 0x170 */ void* _ptmf170;
    /* 0x17C */ void* _ptmf17c;
    /* 0x188 */ Vec _188;
    /* 0x194 */ Vec _194;
    /* 0x1A0 */ Vec _1A0;
    /* 0x1AC */ s32 _1ac;
    /* 0x1B0 */ void* _ptmf1B0;
    /* 0x1B4 */ u8 _1B4;
};

class DustBase {
public: 
    DustBase();
    // no dtor ?

    void init(u16 dustUnk1Count, u16 dustUnk2Count);
    void fn_8012B308(DustUnk2* dustUnk2);
    bool fn_8012F9C8(DustUnk2* dustUnk2);

protected:
    /* 0x000 */ DustUnk2* mDustUnk2;
    /* 0x004 */ DustUnk1* mDustUnk1;
    /* 0x008 */ u8 _008;
    /* 0x00C */ saGrainList<DustUnk1> _00c;
    /* 0x064 */ saGrainList<DustUnk2> _064;
    /* 0x220 */ saGrainList<DustUnk2> _220;
    /* 0x3DC */ void* _3DC;
    /* 0x450 */ Unk450* _450;
    /* 0x454 */ void* _454;
};

#endif
