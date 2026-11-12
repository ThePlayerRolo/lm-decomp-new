#include "Ajioka/Kagu/AEnNoMove1.hpp"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[1] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnNoMove1::state_0_Init, 
        (EnemyStrategyStateFn)&AEnNoMove1::state_0_Behavior
    },
};


void AEnNoMove1::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AEnNoMove1::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnNoMove1::state_0_Init() {
    return true;
}
bool AEnNoMove1::state_0_Behavior() {
    return false;
}

AEnNoMove1::~AEnNoMove1() {
    
}
