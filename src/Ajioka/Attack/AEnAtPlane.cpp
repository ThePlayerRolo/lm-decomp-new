#include "Ajioka/Attack/AEnAtPlane.hpp"


dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[7] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0_Init, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_2_Init, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_2_Behavior
    },

    
    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_3_Init, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_3_Behavior
    },

    
    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_4_Init, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_4_Behavior
    },

    {
        STRAT_STATE_102, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0x102_Init, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0x102_Behavior
    },

    {
        STRAT_STATE_100, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0x100_Init, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0x100_Behavior
    },

    {
        STRAT_STATE_101, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0x101_Init, 
        (EnemyStrategyStateFn)&AEnAtPlane::state_0x101_Behavior
    },
};

AEnAtPlane::AEnAtPlane() {
}


void AEnAtPlane::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AEnAtPlane::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnAtPlane::state_0_Init() {
    return false;
}

bool AEnAtPlane::state_0_Behavior() {
    return true;
}

bool AEnAtPlane::state_2_Init() {
    return false;
}

bool AEnAtPlane::state_2_Behavior() {
    return false;
}

bool AEnAtPlane::state_3_Init() {
    return false;
}

bool AEnAtPlane::state_3_Behavior() {
    return false;
}

bool AEnAtPlane::state_4_Init() {
    return false;
}

bool AEnAtPlane::state_4_Behavior() {
    return false;
}

bool AEnAtPlane::state_0x102_Init() {
    return true;
}

bool AEnAtPlane::state_0x102_Behavior() {
    return true;
}

bool AEnAtPlane::state_0x100_Init() {
    return true;
}

bool AEnAtPlane::state_0x100_Behavior() {
    return true;
}

bool AEnAtPlane::state_0x101_Init() {
    return true;
}

bool AEnAtPlane::state_0x101_Behavior() {
    return true;
}

AEnAtPlane::~AEnAtPlane() {

}
