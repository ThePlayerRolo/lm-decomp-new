#include "Unsorted/PlayerInteraction.hpp"
#include "Unsorted/Player.hpp"
#include "System/MathUtils.hpp"

Player* fn_800AC164(s32 playerID);

PlayerInteractionInfo::PlayerInteractionInfo()
    : _0(10), _4(0), _8(-1), _C(0), _10(0), mSenderID(-1), _18(10), _1C(false), _20(3), _24(0), _28(5), _2C(0), _30(-1), _34(0), _38(-1), _3C(0), _40(0),
      _44(0), _48(100), _4C(100), _50(0), _54(1.0f), _58(1), _5C(0), _60(0), _64(0), _68(0), _6C(-1), _70(0), _74(10), _78(0), _7C(0), _80(0),
      _84(0), _8C(0), _90(0), _94(0), _98(0), _9C(10), _A0(5), _A4(0), _A8(0), _AC(0), _B0(10), _B4(CONVERT_VEC_REF(gZeroVec)),
      _B8(-1), _BC(CONVERT_VEC_REF(gZeroVec)), _C0(0), _C4(0), _C5(1), _C8(-1), _CC(-1), _D0(-1), _D4(0), _D8(0.0f), _DC(0), _E0(-1), _E4(-1.0f),
      _E8(1.0f), _EC(0), _F0(0), _F4(0.0f), _F8(0.0f), _FC(0.3f), _100(-1), _104(0), _108(-1) {
}

JGeometry::TVec3f* fn_800AD504(JGeometry::TVec3f* param_1, s32 senderID) {
    JGeometry::TVec3f* ret = nullptr;

    if (senderID >= 0) {
        ret = &fn_80069130(senderID)->mPosition;
    } else if (param_1 != nullptr) {
        ret = param_1;
    }

    return ret;
}

s32 sendPlayerInteraction(s32 playerID, PlayerInteractionType type, PlayerInteractionInfo* pInteractionInfo) {
    s32 ret = 0;

    Player* player = fn_800AC164(playerID);

    if (player != nullptr) {
        ret = player->receiveInteraction(type, pInteractionInfo);
    }

    return ret;
}
