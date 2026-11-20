#include "Ajioka/Attack/AEnAtCar.hpp"
#include "Sato/EnemyStrategy.hpp"


dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[6] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0_Init, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnAtCar::state_1_Init, 
        (EnemyStrategyStateFn)&AEnAtCar::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnAtCar::state_2_Init, 
        (EnemyStrategyStateFn)&AEnAtCar::state_2_Behavior
    },

    {
        STRAT_STATE_102, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0x102_Init, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0x102_Behavior
    },

    {
        STRAT_STATE_100, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0x100_Init, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0x100_Behavior
    },

    {
        STRAT_STATE_101, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0x101_Init, 
        (EnemyStrategyStateFn)&AEnAtCar::state_0x101_Behavior
    },
};

AEnAtCar::AEnAtCar() {
}


void AEnAtCar::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AEnAtCar::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnAtCar::vt_14() {
    return true;
}



bool AEnAtCar::state_0_Init() {
    return false;
}

bool AEnAtCar::state_0_Behavior() {
    return true;
}

bool AEnAtCar::state_1_Init() {
    return false;
}

bool AEnAtCar::state_1_Behavior() {
    return false;
}

bool AEnAtCar::state_2_Init() {
    return false;
}

bool AEnAtCar::state_2_Behavior() {
    return false;
}

bool AEnAtCar::state_0x102_Init() {
    return true;
}

bool AEnAtCar::state_0x102_Behavior() {
    return true;
}

bool AEnAtCar::state_0x100_Init() {
    return true;
}

bool AEnAtCar::state_0x100_Behavior() {
    return true;
}

bool AEnAtCar::state_0x101_Init() {
    return true;
}

bool AEnAtCar::state_0x101_Behavior() {
    return true;
}

AEnAtCar::~AEnAtCar() {

}
