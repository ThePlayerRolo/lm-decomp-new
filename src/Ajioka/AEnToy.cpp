#include "Ajioka/AEnToy.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[1] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnToy::state_0_Init, 
        (EnemyStrategyStateFn)&AEnToy::state_0_Behavior
    },
};

AEnToy::AEnToy() {}

void AEnToy::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnToy::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnToy::state_0_Init() {
    return true;
}

bool AEnToy::state_0_Behavior() {
    return true;
}


void AEnToy::EnHeyMask_fn_800C62DC() {

}

AEnToy::~AEnToy() {}
