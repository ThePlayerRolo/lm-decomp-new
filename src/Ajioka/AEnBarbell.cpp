#include "Ajioka/AEnBarbell.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0x3] = {
    {
        0, 
        (EnemyStrategyStateFn)&AEnBarbell::state_0_Init, 
        (EnemyStrategyStateFn)&AEnBarbell::state_0_Behavior
    },

    {
        1, 
        (EnemyStrategyStateFn)&AEnBarbell::state_1_Init, 
        (EnemyStrategyStateFn)&AEnBarbell::state_1_Behavior
    },

    {
        2, 
        (EnemyStrategyStateFn)&AEnBarbell::state_2_Init, 
        (EnemyStrategyStateFn)&AEnBarbell::state_2_Behavior
    }
};

void AEnBarbell::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnBarbell::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}


bool AEnBarbell::state_0_Init() {
    return true;
}

bool AEnBarbell::state_0_Behavior() {
    return true;
}

bool AEnBarbell::state_1_Init() {
    return true;
}

bool AEnBarbell::state_1_Behavior() {
    return true;
}

bool AEnBarbell::state_2_Init() {
    return true;
}

bool AEnBarbell::state_2_Behavior() {
    return true;
}

AEnBarbell::~AEnBarbell() {
    
}
