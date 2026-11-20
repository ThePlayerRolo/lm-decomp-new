#include "Ajioka/AEnSkull.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()


static EnemyStrategyState enemiesStates[1] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnSkull::state_0_Init, 
        (EnemyStrategyStateFn)&AEnSkull::state_0_Behavior
    },
};

AEnSkull::AEnSkull() {
    
}

void AEnSkull::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnSkull::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnSkull::EnGhostA_fn_800C8F88() {
    return true;
}

bool AEnSkull::state_0_Init() {
    return false;
}

bool AEnSkull::state_0_Behavior() {
    return true;
}

AEnSkull::~AEnSkull() {
    
}
