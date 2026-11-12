#include "Ajioka/Zako/AEnSimple2.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()


static EnemyStrategyState enemiesStates[3] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnSimple2::state_0_Init, 
        (EnemyStrategyStateFn)&AEnSimple2::state_0_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnSimple2::state_2_Init, 
        (EnemyStrategyStateFn)&AEnSimple2::state_2_Behavior
    },

    
    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnSimple2::state_3_Init, 
        (EnemyStrategyStateFn)&AEnSimple2::state_3_Behavior
    },
};

float lbl_80368134[] = {50.0, 0.0, 0.0};


AEnSimple2::AEnSimple2() {

}

AEnSimple2::~AEnSimple2() {
    
}

void AEnSimple2::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnSimple2::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnSimple2::vt_14() {
    return true;
}


bool AEnSimple2::state_0_Init() {
    return true;
}

bool AEnSimple2::state_0_Behavior() {
    return true;
}

bool AEnSimple2::state_2_Init() {
    return true;
}

bool AEnSimple2::state_2_Behavior() {
    return true;
}

bool AEnSimple2::state_3_Init() {
    return true;
}

bool AEnSimple2::state_3_Behavior() {
    return true;
}


bool AEnSimple2::onSprayedWithWater(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnSimple2::onSprayedWithFire(Koga::CharacterEvent* msg) {
    return true;
}


void AEnSimple2::AEnZakoBase_fn_800F5FA8() {
}
