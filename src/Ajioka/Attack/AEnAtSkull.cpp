#include "Ajioka/Attack/AEnAtSkull.hpp"


dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[6] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0_Init, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_1_Init, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_2_Init, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_2_Behavior
    },

    {
        STRAT_STATE_102, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0x102_Init, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0x102_Behavior
    },

    {
        STRAT_STATE_100, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0x100_Init, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0x100_Behavior
    },

    {
        STRAT_STATE_101, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0x101_Init, 
        (EnemyStrategyStateFn)&AEnAtSkull::state_0x101_Behavior
    },
};

AEnAtSkull::AEnAtSkull() {
    _54 = false;
}

AEnAtSkull::~AEnAtSkull() {
    if (mCurrentState != 0 && _64 != nullptr && _60 == 1) {
        // fn_80117A68(&_60, 0);
    }
    if (_54) {
        // fn_80117B9C(&_60);
    }
}

void AEnAtSkull::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AEnAtSkull::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnAtSkull::vt_14() {
    return true;
}



bool AEnAtSkull::state_0_Init() {
    return false;
}

bool AEnAtSkull::state_0_Behavior() {
    return false;
}

bool AEnAtSkull::state_1_Init() {
    return false;
}

bool AEnAtSkull::state_1_Behavior() {
    return false;
}

bool AEnAtSkull::state_2_Init() {
    return false;
}

bool AEnAtSkull::state_2_Behavior() {
    return false;
}

bool AEnAtSkull::state_0x102_Init() {
    return true;
}

bool AEnAtSkull::state_0x102_Behavior() {
    return true;
}

bool AEnAtSkull::state_0x100_Init() {
    return true;
}

bool AEnAtSkull::state_0x100_Behavior() {
    return true;
}

bool AEnAtSkull::state_0x101_Init() {
    return true;
}

bool AEnAtSkull::state_0x101_Behavior() {
    return true;
}


// From EnAttackBase -> Koga::CharacterEventObserver

bool AEnAtSkull::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnAtSkull::onSprayedWithWater(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnAtSkull::onSprayedWithFire(Koga::CharacterEvent* msg) {
    return false;
}
bool AEnAtSkull::onSprayedWithIce(Koga::CharacterEvent* msg) {
    return false;
}


bool AEnAtSkull::vt_18(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnAtSkull::onFishingBegin(Koga::CharacterEvent* msg) {
    return false;
}
bool AEnAtSkull::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return false;
}
