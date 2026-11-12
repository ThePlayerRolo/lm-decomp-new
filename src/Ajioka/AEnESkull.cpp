#include "Ajioka/AEnESkull.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[2] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnESkull::state_0_Init, 
        (EnemyStrategyStateFn)&AEnESkull::state_0_Behavior
    },

    {
        STRAT_STATE_A, 
        (EnemyStrategyStateFn)&AEnESkull::state_0xA_Init, 
        (EnemyStrategyStateFn)&AEnESkull::state_0xA_Behavior
    },
};

AEnESkull::AEnESkull() {
    
}

void AEnESkull::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnESkull::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnESkull::state_0_Init() {
    return false;
}

bool AEnESkull::state_0_Behavior() {
    return false;
}

bool AEnESkull::state_0xA_Init() {
    return false;
}

bool AEnESkull::state_0xA_Behavior() {
    return false;
}


bool AEnESkull::onCaptureBegin(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnESkull::onCaptureEnd(Koga::CharacterEvent* msg) {
    return true;
}

void AEnESkull::EnGhostA_fn_800C8ECC() {

}

AEnESkull::~AEnESkull() {
    
}
