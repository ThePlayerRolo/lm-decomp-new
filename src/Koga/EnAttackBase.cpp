#include <JSystem/JKernel/JKRMemArchive.hpp>

#include "Koga/EnAttackBase.hpp"
#include "Koga/EnTypesManager.hpp"
#include "Koga/Params.hpp"
#include "Unsorted/PlayerInteraction.hpp"

struct UnkStruct1 {
    s32 _0;
    s32 _4;
    s32 _8;
    s32 _c;
};

JKRMemArchive* fn_80066FB4();

static const s32 rodata[] = { 6, 7, 5, 0}; // Maybe the 0 is not in this table and it's a alignment

EnAttackBaseParams* EnAttackBase::vt_70()  { 
    return &mParams; 
}

void EnAttackBase::EnAttackBase_fn_800DDD5C(void*) {
}


bool EnAttackBase::EnAttackBase_fn_800DDDD8(const char* filePath) {
    return vt_70()->mParams.load(filePath, fn_80066FB4());
}

void EnAttackBase::sendAttack() {
    PlayerInteractionInfo info;
    info.mSenderID = getZako()->getCharacter()->get_38();
    info._18 = vt_70()->mDamage.get();
    info._20 = EnAttackBase_fn_800DDF58();
    info._24 = 0;
    info._1C = true;
    sendPlayerInteraction(getZako()->getPlayerID(), INTERACTION_ATTACK, &info);
}

void EnAttackBase::EnAttackBase_fn_800DDEC8() {
    _1C = 0;
}


bool EnAttackBase::EnAttackBase_fn_800DDED4() {
    s32 disappearFrame = Koga::EnTypesManager::getEnemyDisappearFrame(getZako()->getCharacter()->get_3C());
    if (disappearFrame == 0)
        return false;
    
    if (disappearFrame <= ++_1C) { // && fn_800BA380() < 0.01f){ 1% random
        setNextState(0x102);
        return true;    
    }

    return false;
}

s32 EnAttackBase::EnAttackBase_fn_800DDF58() {
    return rodata[vt_70()->mAttackType.get()];
}
