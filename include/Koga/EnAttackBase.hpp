#ifndef EN_ATTACK_BASE_H_
#define EN_ATTACK_BASE_H_

#include "Ajioka/Attack/AEnAtStructs.hpp"
#include "Koga/BaseParam.hpp"
#include "Koga/ParamInst.hpp"
#include "Koga/Params.hpp"
#include <Koga/CharacterEventObserver.hpp>
#include <Sato/EnemyStrategy.hpp>
#include "Sato/EnZako.hpp"

class EnAttackBaseParams {
public:
    EnAttackBaseParams() :
        mParams("/param/th/EnAttackBase.prm"),
        mDamage(&mParams, 0, "mDamage", TBaseParam::calcKeyCode("mDamage")),
        mAttackType(&mParams, 0, "mAttackType", TBaseParam::calcKeyCode("mAttackType"))
    {
    }

public:
    /* 0x00 */ TParams mParams;
    /* 0x0C */ TParamT<long> mDamage;
    /* 0x20 */ TParamT<short> mAttackType;
};

class EnAttackBase : public EnemyStrategy, public Koga::CharacterEventObserver {
public:
    EnAttackBase() {}
    /* 0x08 */ virtual ~EnAttackBase() { };
    /* 0x70 */ virtual EnAttackBaseParams* vt_70();

    void EnAttackBase_fn_800DDD5C(void*);
    bool EnAttackBase_fn_800DDDD8(const char* filePath);
    void sendAttack();
    void EnAttackBase_fn_800DDEC8();
    bool EnAttackBase_fn_800DDED4();
    s32 EnAttackBase_fn_800DDF58();

public:
    /* 0x18 */ const AEnAtStruct2* _18;
    /* 0x1C */ s32 _1C;
    /* 0x20 */ EnAttackBaseParams mParams;
};

#endif
