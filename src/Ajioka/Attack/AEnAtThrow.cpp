#include "Ajioka/Attack/AEnAtThrow.hpp"


dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[7] = {
    {
        0, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0_Init, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0_Behavior
    },

    {
        1, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_1_Init, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_1_Behavior
    },

    {
        2, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_2_Init, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_2_Behavior
    },

    {
        3, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_3_Init, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_3_Behavior
    },

    {
        0x102, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0x102_Init, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0x102_Behavior
    },

    {
        0x100, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0x100_Init, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0x100_Behavior
    },

    {
        0x101, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0x101_Init, 
        (EnemyStrategyStateFn)&AEnAtThrow::state_0x101_Behavior
    },
};

AEnAtThrow::AEnAtThrow() {
    _54 = false;
}

AEnAtThrow::~AEnAtThrow() {
    if (mCurrentState != 0 && _64 != nullptr && _60 == 1) {
        // fn_80117A68(&_60, 0);
    }
    if (_54) {
        // fn_80117B9C(&_60);
    }
}

void AEnAtThrow::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AEnAtThrow::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnAtThrow::vt_14() {
    return true;
}



bool AEnAtThrow::state_0_Init() {
    return false;
}

bool AEnAtThrow::state_0_Behavior() {
    return false;
}

bool AEnAtThrow::state_1_Init() {
    return false;
}

bool AEnAtThrow::state_1_Behavior() {
    return false;
}

bool AEnAtThrow::state_2_Init() {
    return false;
}

bool AEnAtThrow::state_2_Behavior() {
    return false;
}

bool AEnAtThrow::state_3_Init() {
    return false;
}

bool AEnAtThrow::state_3_Behavior() {
    return false;
}

bool AEnAtThrow::state_0x102_Init() {
    return true;
}

bool AEnAtThrow::state_0x102_Behavior() {
    return true;
}

bool AEnAtThrow::state_0x100_Init() {
    return true;
}

bool AEnAtThrow::state_0x100_Behavior() {
    return true;
}

bool AEnAtThrow::state_0x101_Init() {
    return true;
}

bool AEnAtThrow::state_0x101_Behavior() {
    return true;
}


// From EnAttackBase -> Koga::CharacterEventObserver

bool AEnAtThrow::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnAtThrow::vt_18(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnAtThrow::onSprayedWithWater(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnAtThrow::onSprayedWithFire(Koga::CharacterEvent* msg) {
    return false;
}
bool AEnAtThrow::onSprayedWithIce(Koga::CharacterEvent* msg) {
    return false;
}
bool AEnAtThrow::onFishingBegin(Koga::CharacterEvent* msg) {
    return false;
}
bool AEnAtThrow::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return false;
}
