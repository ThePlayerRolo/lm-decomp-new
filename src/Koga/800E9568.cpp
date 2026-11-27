#include <string.h>

#include "Koga/800E9568.hpp"
#include "Koga/800E634C.hpp"
#include "Koga/CharacterEventObserver.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Koga/MissionMode.hpp"
#include "Koga/JMPMessage.hpp"
#include "Sato/EnThought.hpp"
#include "Koga/EnTypesManager.hpp"
#include "Unsorted/Character.hpp"
#include "Koga/ToolData.hpp"


Vec* fn_800E9568(s32 appearSlotIndex) {
    return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5564(appearSlotIndex);
}

s32 fn_800E9594(s32 appearSlotIndex) {
    return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E55AC(appearSlotIndex);
}

// https://decomp.me/scratch/Zhrs6
BOOL fn_800E95C0(s32 expectedPoint, JGeometry::TVec3f* pParam_1, u16* out) {
    ToolDataRef* appearEntry = Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5488(expectedPoint);
    Koga::ToolData* pCharInfo = appearEntry->getToolData();
    s32 entryIndex = appearEntry->getEntryIndex();
    bool bPointFound = false;

    if (!appearEntry->isValid()) { //if (pCharInfo != nullptr && 0 <= entryIndex) { //if (appearEntry.isValid()) {
        return false;
    }

    pCharInfo->getValue(entryIndex, "pos_x", &pParam_1->x);
    pCharInfo->getValue(entryIndex, "pos_y", &pParam_1->y);
    pCharInfo->getValue(entryIndex, "pos_z", &pParam_1->z);

    if (out != nullptr) {
        u32 dir = 0;
        pCharInfo->getValue(entryIndex, "dir_y", &dir);
        *out = dir;
    }

    return true;
}

s32 fn_800E96B8(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* pParam_2, f32 param_3) {
    return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5660(pParam_1, pParam_2, param_3);
}

s32 fn_800E96E8(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* pParam_2) {
    return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E56E4(pParam_1, pParam_2);
}

s32 fn_800E971C(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* pParam_2) {
    return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5784(pParam_1, pParam_2);
}

Player* getPlayer(s32 param_1) {
    return Koga::MissionMode::getMissionMode()->getEnManager()->getPlayer(param_1);
}

s32 fn_800E977C(s32 param_1, s32 param_2) {
    return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5868(param_1, param_2);
}

void fn_800E97B0(s32 param_1) {
    Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E59D4(param_1);
}

Character* fn_800E97DC(char* param_1) {
    const char* temp2;
    unkEnManager1Wrapper temp = unkEnManager1Wrapper();
    fn_800E98E0(&temp);

    for (unkEnManager1* currElm = temp.mBegin; currElm != temp.mEnd; currElm++) {
        if (currElm->mState != CHARSTATE_2) {
            continue;
        }
        ToolDataRef mRef = currElm->_0->getToolDataRef();
        const char* codeName;

        if (mRef.isValid() && !mRef.getToolData()->getValue(mRef.getEntryIndex(), "CodeName", &codeName)) {
                Character* pChar = currElm->getCharacter();
                temp2 = Koga::EnTypesManager::fn_800DAAF8(pChar->get_3C());
        }

        if (strcmp(temp2, param_1) == 0) {
            return currElm->getCharacter();
        }
    }

    return nullptr;
}

void fn_800E98E0(unkEnManager1Wrapper* pDest) {
    Koga::EnManager* pMgr = Koga::MissionMode::getMissionMode()->getEnManager();
    pMgr->fn_800E5A00(pDest, pMgr);
}

BOOL fn_800E9914(const char* param_1, s32 param_2) {
    return Koga::MissionMode::sMissionMode->mJmpMsgSender->fn_800EAA00(param_1, param_2);
}

s32 fn_800E9948(const char* param_1) {
    return Koga::MissionMode::sMissionMode->getEnManager()->fn_800E5BF8(param_1);
}

s32 fn_800E9974(const char* param_1) {
    return Koga::MissionMode::sMissionMode->getEnManager()->fn_800E5D18(param_1);
}

// https://decomp.me/scratch/LLh5c
// unkEnManager1::~unkEnManager1() {
//     if (_0 != nullptr) {
//         // Call some destructor through _0+0x804
//     }
// }

// TODO Leaving unmatched until DAC84 is confirmed an s32 or u32
// https://decomp.me/scratch/EmrGG
void unkEnManager1::fn_800E9A0C(EnThought* pParam_1) {
    _0 = pParam_1;
    _8 = Koga::EnTypesManager::fn_800DAC84(pParam_1->getCharacter()->get_3C());
    mState = CHARSTATE_2;
    _C = 0;
}

// https://decomp.me/scratch/IUVOm
bool unkEnManager1::fn_800E9A58(s32 param_1) {
    mState = CHARSTATE_1;
    _C = 0;
    bool temp = _0->fn_800C15E0(param_1);

    if (temp == 0) {
        return false;
    }

    fn_800E9CDC();
    _0->getStrategy()->init();

    return true;
}

// 99%, some stack mismanagement
void unkEnManager1::fn_800E9ACC() {
    mState = CHARSTATE_1;
    _0->fn_800C17EC();
    JGeometry::TVec3f defaultPos = JGeometry::TVec3f(-32000.0f);
    getCharacter()->fn_80067CB0(defaultPos.x, defaultPos.y, defaultPos.z);
}

void unkEnManager1::fn_800E9B44() {
    if (mState == CHARSTATE_2) {
        _0->fn_800BF81C();
    }
}

Character* unkEnManager1::getCharacter() {
    if (_0 == nullptr) {
        return nullptr;
    }

    return _0->getCharacter();
}

void unkEnManager1::fn_800E9CDC() {
    Character* cTemp;
    ToolDataRef ref = _0->getToolDataRef();

    if (!ref.isValid()) {
        return;
    }

    fn_800E6ED0(_0);

    u8 invisible;
    ref.getToolData()->getValue(ref.getEntryIndex(), "invisible", &invisible);
    if (invisible != 0) {
        if (_0 == nullptr) {
            cTemp = _0->getCharacter();
        }
        cTemp->mAlpha1 = 0;
        cTemp->mAlpha2 = 0;
    } else {
        if (_0 == nullptr) {
            cTemp = _0->getCharacter();
        }
        cTemp->mAlpha1 = -1;
        cTemp->mAlpha2 = -1;
    }
}

void unkEnManager1::fn_800E9B74() {
    if (mState != CHARSTATE_2) return;
    Character* character = getCharacter();
}

bool unkEnManager1::fn_800E9C38(const Koga::CharacterEvent& rEvent) {
    return _0->fn_800C0F08(rEvent);
}
