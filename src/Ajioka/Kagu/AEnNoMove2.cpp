#include "Ajioka/Kagu/AEnNoMove2.hpp"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[2] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnNoMove2::state_0_Init, 
        (EnemyStrategyStateFn)&AEnNoMove2::state_0_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnNoMove2::state_2_Init, 
        (EnemyStrategyStateFn)&AEnNoMove2::state_2_Behavior
    },
};


void AEnNoMove2::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AEnNoMove2::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnNoMove2::state_0_Init() {
    return false;
}
bool AEnNoMove2::state_0_Behavior() {
    return false;
}

bool AEnNoMove2::state_2_Init() {
    return true;
}
bool AEnNoMove2::state_2_Behavior() {
    return false;
}

bool AEnNoMove2::onSprayedWithWater(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnNoMove2::onSprayedWithFire(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnNoMove2::onSprayedWithIce(Koga::CharacterEvent* msg) {
    return false;
}


AEnNoMove2::~AEnNoMove2() {
    
}
