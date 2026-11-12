#ifndef MOVE_OBJ_HPP
#define MOVE_OBJ_HPP

#include <JSystem/JAudio/JAInterface/JAIAnimation.hpp>
#include <JSystem/JGeometry/JGVec3.hpp>
#include <types.h>
#include <dolphin/mtx.h>

// 0xe3, 0xe7
class MoveObj {
public:
    MoveObj();

    /* 0x08 */ virtual ~MoveObj();
    /* 0x0C */ virtual void vt_0C(u16, u16, u16);

    // Defined in the EnManager TU, but exist in this class based on the split, I think.
    MoveObj* fn_800E7414(u32 id);
    MoveObj* fn_800E7510(MoveObj*);
    void fn_800E760C();
    void fn_800E7628();
    bool fn_800E7650();

    
    inline s32 get_38() const { return _38; }
    inline s32 get_3C() const { return _3C; }

    void fn_80067C30(const Vec*);
    void fn_80067CB0(f32 var1, f32 var2, f32 var3); //This may be protected but TU 800E9568 calls it, may need to do something different.

protected:    
    u16 fn_80067D3C(u16);
    void fn_80067F84();
    bool fn_800681E8(const char*);
    void fn_80068238(s32);
    void fn_80068268(s32, JGeometry::TVec3<f32>&);
    void fn_800682DC(s16);
    void fn_800685B0();

    // Maybe header defined
    void fn_80068DAC(s16, s16, s16);

public:
    inline void setE3andE7() {
        _E3 = false;
        _E7 = false;
    }

    /* 0x004 */ u8 _4[0x34];
    /* 0x038 */ s32 _38;
    /* 0x03C */ s32 _3C;
    /* 0x040 */ s32 _40;

    /* 0x044 */ JGeometry::TVec3<f32> _44;
    /* 0x050 */ JGeometry::TVec3<f32> _50;
    /* 0x05c */ JGeometry::TVec3<f32> _5C;
    /* 0x068 */ f32 _68;
    /* 0x06C */ Vec _6C;
    /* 0x078 */ Vec _78;
    /* 0x084 */ s16 _84;
    /* 0x086 */ s16 _86;
    /* 0x088 */ s16 _88;
    /* 0x08A */ s16 _8A;
    /* 0x08C */ s16 _8C;
    /* 0x08E */ s16 _8E;

    /* 0x090 */ Vec _90; // set the same value on all 3 axes in AEnEBone. Scale ? 
    /* 0x09C */ u8 _9C[0xB4 - 0x9C];

    /* 0x0B4 */ u32 _B4;
    
    /* 0x0B8 */ u32 _B8;
    /* 0x0BC */ u32 _BC;
    /* 0x0C0 */ u32 _C0;
    /* 0x0C4 */ u32 _C4;
    /* 0x0C8 */ u8 _C8[0xD8 - 0xC8];

    /* 0x0D8 */ f32 _D8;
    /* 0x0DC */ void* _DC;
    /* 0x0E0 */ bool _E0;
    /* 0x0E1 */ bool _E1;
    /* 0x0E2 */ bool _E2;
    /* 0x0E3 */ u8 _E3;
    /* 0x0E4 */ bool _E4;
    /* 0x0E5 */ bool _E5;
    /* 0x0E6 */ bool _E6;
    /* 0x0E7 */ u8 _E7;
    
    /* 0x0E8 */ u32 _E8;
    /* 0x0EC */ u32 _EC;
    /* 0x0F0 */ u32 _F0;
    /* 0x0F4 */ u32 _F4;
    /* 0x0F8 */ s16 _F8;
    /* 0x0FA */ s16 _FA;
    /* 0x0FC */ u8 _FC;
    /* 0x100 */ JGeometry::TVec3<f32> _100;
    /* 0x10C */ JGeometry::TVec3<f32> _10C;
    /* 0x118 */ u8 _118[0x53C - 0x118];

    /* 0x53C */ JAIAnimeSound mAnimeSound;

    /* 0x5D4 */ u8 _5D4[0x788 - 0x5d4];

    /* 0x788 */ u8 _size; // TEMP ! USED JUST FOR MY CALCULATION FOR THE SIZE TO NOT DESTROY EVERYTHING
};

#endif
