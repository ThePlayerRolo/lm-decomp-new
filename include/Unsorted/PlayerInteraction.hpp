#ifndef _PLAYER_INTERACTION_HPP
#define _PLAYER_INTERACTION_HPP

#include <JSystem/JGeometry/JGVec3.hpp>

enum PlayerInteractionType {
    /* 0x03 */ INTERACTION_ATTACK = 0x3,
    /* 0x21 */ INTERACTION_KEY_GET = 0x21,
};

class PlayerInteractionInfo {
public:
    PlayerInteractionInfo();

    /* 0x000 */ s32 _0;
    /* 0x004 */ s32 _4;
    /* 0x008 */ s32 _8;
    /* 0x00C */ s32 _C;
    /* 0x010 */ s32 _10;
    /* 0x014 */ s32 mSenderID;
    /* 0x018 */ s32 _18;
    /* 0x01C */ bool _1C;
    /* 0x020 */ s32 _20;
    /* 0x024 */ s32 _24;
    /* 0x028 */ s32 _28;
    /* 0x02C */ s32 _2C;
    /* 0x030 */ s32 _30;
    /* 0x034 */ s32 _34;
    /* 0x038 */ s32 _38;
    /* 0x03C */ s32 _3C;
    /* 0x040 */ s32 _40;
    /* 0x044 */ s32 _44;
    /* 0x048 */ s32 _48;
    /* 0x04C */ s32 _4C;
    /* 0x050 */ s32 _50;
    /* 0x054 */ f32 _54;
    /* 0x058 */ s32 _58;
    /* 0x05C */ s32 _5C;
    /* 0x060 */ s32 _60;
    /* 0x064 */ s32 _64;
    /* 0x068 */ s32 _68;
    /* 0x06C */ s32 _6C;
    /* 0x070 */ s32 _70;
    /* 0x074 */ s32 _74;
    /* 0x078 */ s32 _78;
    /* 0x07C */ s32 _7C;
    /* 0x080 */ s32 _80;
    /* 0x084 */ s32 _84;
    /* 0x088 */ u8 _88;
    /* 0x08C */ s32 _8C;
    /* 0x090 */ s32 _90;
    /* 0x094 */ s32 _94;
    /* 0x098 */ s32 _98;
    /* 0x09C */ s32 _9C;
    /* 0x0A0 */ s32 _A0;
    /* 0x0A4 */ s32 _A4;
    /* 0x0A8 */ u8 _A8;
    /* 0x0AC */ s32 _AC;
    /* 0x0B0 */ s32 _B0;
    /* 0x0B4 */ JGeometry::TVec3f& _B4;
    /* 0x0B8 */ s32 _B8;
    /* 0x0BC */ JGeometry::TVec3f& _BC;
    /* 0x0C0 */ s32 _C0;
    /* 0x0C4 */ u8 _C4;
    /* 0x0C5 */ u8 _C5;
    /* 0x0C8 */ s32 _C8;
    /* 0x0CC */ s32 _CC;
    /* 0x0D0 */ s32 _D0;
    /* 0x0D4 */ s32 _D4;
    /* 0x0D8 */ f32 _D8;
    /* 0x0DC */ s32 _DC;
    /* 0x0E0 */ s32 _E0;
    /* 0x0E4 */ f32 _E4;
    /* 0x0E8 */ f32 _E8;
    /* 0x0EC */ s32 _EC;
    /* 0x0F0 */ s32 _F0;
    /* 0x0F4 */ f32 _F4;
    /* 0x0F8 */ f32 _F8;
    /* 0x0FC */ f32 _FC;
    /* 0x100 */ s32 _100;
    /* 0x104 */ s32 _104;
    /* 0x108 */ s32 _108;
};

s32 sendPlayerInteraction(s32 playerID, PlayerInteractionType type, PlayerInteractionInfo* pInteractionInfo);

#endif
