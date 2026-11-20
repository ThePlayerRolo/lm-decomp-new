#include <JSystem/JKernel/JKRMemArchive.hpp>

#include "Koga/EnAttackBase.hpp"
#include "Koga/EnTypesManager.hpp"
#include "Koga/Params.hpp"

struct UnkStruct1 {
    s32 _0;
    s32 _4;
    s32 _8;
    s32 _c;
};

struct UnkStruct2 {
    UnkStruct2(); // fn_800AD3C0

    /* 0x000 */ u8 _00[0x14];
    /* 0x014 */ s32 _14;
    /* 0x018 */ s32 _18;
    /* 0x01C */ bool _1C;
    /* 0x020 */ s32 _20;
    /* 0x024 */ s32 _24;
    /* 0x028 */ u8 _28[0x10C - 0x28];
};

void fn_800AD54C(s32, int, UnkStruct2*);
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

void EnAttackBase::EnAttackBase_fn_800DDE3C() {
    UnkStruct2 info;
    info._14 = getZako()->getCharacter()->get_38();
    info._18 = vt_70()->mDamage.get();
    info._20 = EnAttackBase_fn_800DDF58();
    info._24 = 0;
    info._1C = true;
    fn_800AD54C(getZako()->get_950(), 3, &info);
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
