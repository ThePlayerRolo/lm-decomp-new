#include "Ajioka/Beam/AEnBeam1.hpp"
#include "macros.h"


dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[6] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnBeam1::state_0_Init, 
        (EnemyStrategyStateFn)&AEnBeam1::state_0_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnBeam1::state_2_Init, 
        (EnemyStrategyStateFn)&AEnBeam1::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnBeam1::state_3_Init, 
        (EnemyStrategyStateFn)&AEnBeam1::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnBeam1::state_4_Init, 
        (EnemyStrategyStateFn)&AEnBeam1::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnBeam1::state_5_Init, 
        (EnemyStrategyStateFn)&AEnBeam1::state_5_Behavior
    },

    {
        STRAT_STATE_6, 
        (EnemyStrategyStateFn)&AEnBeam1::state_6_Init, 
        (EnemyStrategyStateFn)&AEnBeam1::state_6_Behavior
    },
};

static char lbl_804D426C[] = "FLYT";
static char lbl_804D4274[] = "NORMAL";

void AEnBeam1::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnBeam1::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }    
}

bool AEnBeam1::vt_14() {
    return false;
}

// For EnemyStrategyState
bool AEnBeam1::state_0_Init() {
    return true;
}

bool AEnBeam1::state_0_Behavior() {
    return true;
}

bool AEnBeam1::state_2_Init() {
    return true;
}

bool AEnBeam1::state_2_Behavior() {
    return true;
}

bool AEnBeam1::state_3_Init() {
    return true;
}

bool AEnBeam1::state_3_Behavior() {
    return true;
}

bool AEnBeam1::state_4_Init() {
    return true;
}

bool AEnBeam1::state_4_Behavior() {
    return true;
}

bool AEnBeam1::state_5_Init() {
    return true;
}

bool AEnBeam1::state_5_Behavior() {
    return true;
}

bool AEnBeam1::state_6_Init() {
    return true;
}

bool AEnBeam1::state_6_Behavior() {
    return true;
}


// From AEnBeamBase
void AEnBeam1::AEnBeamBase_fn_800F6DF8() {

}

// From AEnZakoBase
void AEnBeam1::AEnZakoBase_fn_800F5FA8() {

}

void AEnBeam1::AEnZakoBase_fn_800F6010() {

}

// From AEnBeamBase
void AEnBeam1::AEnBeamBase_fn_800F700C() {

}

void AEnBeam1::AEnBeamBase_fn_800F7120() {

}

AEnBeam1::~AEnBeam1() {
    
}
