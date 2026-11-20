#include "Ajioka/Zako/AEnSimple1.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()


static EnemyStrategyState enemiesStates[4] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnSimple1::state_0_Init, 
        (EnemyStrategyStateFn)&AEnSimple1::state_0_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnSimple1::state_3_Init, 
        (EnemyStrategyStateFn)&AEnSimple1::state_3_Behavior
    },

    
    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnSimple1::state_4_Init, 
        (EnemyStrategyStateFn)&AEnSimple1::state_4_Behavior
    },

    
    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnSimple1::state_5_Init, 
        (EnemyStrategyStateFn)&AEnSimple1::state_5_Behavior
    },
};


float data_float[] = {8.0, 0.0, 12.0,0.3, 1.0, 0.8, 2.7, 5.5,
                    4.0, 80.0,100.0,  100.0,  60.0,90.0,60.0,12.0,
                    32.0,32.0,12.0,12.0,16.0,2.0, 2.0, 8.0,
                0.0, 0.0, 30.0};
int data_int[] = {16, 16, 24};

AEnSimple1::AEnSimple1() {

}

void AEnSimple1::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnSimple1::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnSimple1::vt_14() {
    return true;
}


bool AEnSimple1::state_0_Init() {
    return false;
}

bool AEnSimple1::state_0_Behavior() {
    return false;
}

bool AEnSimple1::state_3_Init() {
    return false;
}

bool AEnSimple1::state_3_Behavior() {
    return false;
}

bool AEnSimple1::state_4_Init() {
    return false;
}

bool AEnSimple1::state_4_Behavior() {
    return false;
}

bool AEnSimple1::state_5_Init() {
    return false;
}

bool AEnSimple1::state_5_Behavior() {
    return false;
}

AEnSimple1::~AEnSimple1() {
    
}
