#include "Ajioka/AEnPoltergeist.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[6] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_0_Init, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_1_Init, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_2_Init, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_3_Init, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_4_Init, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_5_Init, 
        (EnemyStrategyStateFn)&AEnPoltergeist::state_5_Behavior
    }
};

AEnPoltergeist::AEnPoltergeist() {}
AEnPoltergeist::~AEnPoltergeist() {}


void AEnPoltergeist::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnPoltergeist::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnPoltergeist::vt_14() {
    return false;
}

bool AEnPoltergeist::state_0_Init() {
    return true;
}

bool AEnPoltergeist::state_0_Behavior() {
    return true;
}

bool AEnPoltergeist::state_1_Init() {
    return true;
}

bool AEnPoltergeist::state_1_Behavior() {
    return true;
}

bool AEnPoltergeist::state_2_Init() {
    return true;
}

bool AEnPoltergeist::state_2_Behavior() {
    return true;
}

bool AEnPoltergeist::state_3_Init() {
    return true;
}

bool AEnPoltergeist::state_3_Behavior() {
    return true;
}

bool AEnPoltergeist::state_4_Init() {
    return true;
}

bool AEnPoltergeist::state_4_Behavior() {
    return true;
}

bool AEnPoltergeist::state_5_Init() {
    return true;
}

bool AEnPoltergeist::state_5_Behavior() {
    return true;
}

bool AEnPoltergeist::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return true;
}
