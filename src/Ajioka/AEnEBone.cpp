#include "Ajioka/AEnEBone.hpp"
#include "Unsorted/Character.hpp"
#include "Sato/EnZako.hpp"
#include "Unsorted/MathUtils.hpp"
#include "dolphin/mtx.h"
#include "Unsorted/globals.hpp"

void fn_800F4374(EnZako*, s32, s32);

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[3] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnEBone::state_0_Init, 
        (EnemyStrategyStateFn)&AEnEBone::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnEBone::state_1_Init, 
        (EnemyStrategyStateFn)&AEnEBone::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnEBone::state_2_Init, 
        (EnemyStrategyStateFn)&AEnEBone::state_2_Behavior
    },
};

static s32 flyFramesDuration = 61;
static f32 lbl_804D4AFC = 2.0f;
static f32 flyGravity = 0.8f;

static Vec pos = { -3300, 100, -2800 };

void AEnEBone::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnEBone::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnEBone::state_0_Init() {
    EnZako* zako = getZako();
    Character* enemy = zako->getCharacter();

    enemy->_E3 = -1;
    enemy->_E7 = -1;
    zako->getCharacter()->_40 &= ~0xC400;
    zako->fn_800BF384();

    return true;
}

bool AEnEBone::state_0_Behavior() {
    setNextState(1);

    return true;
}

bool AEnEBone::state_1_Init() {
    EnZako* zako = getZako();
    Vec velocity;
    PSVECSubtract(&pos, (Vec*)&zako->getCharacter()->_44, &velocity);

    f32 vx = velocity.x / flyFramesDuration;
    velocity.x = vx;

    f32 vy = velocity.y / flyFramesDuration;
    f32 h = 0.5f * (flyGravity * flyFramesDuration);
    velocity.y = vy + h;

    f32 vz = velocity.z / flyFramesDuration;
    velocity.z = vz;

    zako->getCharacter()->fn_80067C30(&velocity);
    s16 angle = atan2BAM(velocity.z, velocity.x);
    zako->getCharacter()->_8A = angle;

    zako->fn_800BFB98("FLYC", 0);

    return true;
}

bool AEnEBone::state_1_Behavior() {
    EnZako* zako = getZako();
    Vec vel = zako->getCharacter()->_6C;
    f32 vy = vel.y - flyGravity;
    vel.y = vy;
    zako->getCharacter()->fn_80067C30(&vel);

    f32 timer = mTimer;
    f32 frames = flyFramesDuration;
    f32 v1 = lbl_804D4AFC * timer;
    f32 v2 = v1 / frames;

    Character* chr = zako->getCharacter();
    f32 z = v2;
    f32 y = v2;
    f32 x = v2;
    chr->_90.z = z;
    chr->_90.y = y;
    chr->_90.x = x;

    if (mTimer >= flyFramesDuration) {
        setNextState(2);
    }

    return true;
}

bool AEnEBone::state_2_Init() {
    getZako()->getCharacter()->_D8 = 0.0f;
    getZako()->fn_800BF3E0();

    return true;
}

bool AEnEBone::state_2_Behavior() {
    getZako()->getCharacter()->fn_80067C30(&gZeroVec);

    return true;
}

bool AEnEBone::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    if (mCurrentState != 0) {
        fn_800F4374(getZako(), 0, -1);
    }

    return true;
}

AEnEBone::~AEnEBone() {}
