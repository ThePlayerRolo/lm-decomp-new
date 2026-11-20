#include "Ajioka/Beam/AEnBeam2.hpp"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[5] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnBeam2::state_0_Init, 
        (EnemyStrategyStateFn)&AEnBeam2::state_0_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnBeam2::state_2_Init, 
        (EnemyStrategyStateFn)&AEnBeam2::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnBeam2::state_3_Init, 
        (EnemyStrategyStateFn)&AEnBeam2::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnBeam2::state_4_Init, 
        (EnemyStrategyStateFn)&AEnBeam2::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnBeam2::state_5_Init, 
        (EnemyStrategyStateFn)&AEnBeam2::state_5_Behavior
    },
};

void AEnBeam2::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnBeam2::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }    
}

// PTMF EnemyStrategy
bool AEnBeam2::state_0_Init() {
    return true;
}

bool AEnBeam2::state_0_Behavior() {
    return true;
}

bool AEnBeam2::state_2_Init() {
    return true;
}

bool AEnBeam2::state_2_Behavior() {
    return false;
}

bool AEnBeam2::state_3_Init() {
    return true;
}

bool AEnBeam2::state_3_Behavior() {
    return true;
}

bool AEnBeam2::state_4_Init() {
    return true;
}

bool AEnBeam2::state_4_Behavior() {
    return false;
}

bool AEnBeam2::state_5_Init() {
    return true;
}

bool AEnBeam2::state_5_Behavior() {
    return true;
}

// From Koga::CharacterEventObserver
bool AEnBeam2::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return true;
}

// From AEnBeamBase, AEnZakoBase and this class (yes, it's ordered)
void AEnBeam2::AEnBeamBase_fn_800F6DF8() {

}

void AEnBeam2::AEnZakoBase_fn_800F5F4C() {

}

void AEnBeam2::AEnBeam2_fn_800FA11C() {

}

void AEnBeam2::AEnZakoBase_fn_800F6010() {

}

void AEnBeam2::AEnBeamBase_fn_800F700C() {

}
AEnBeam2::~AEnBeam2() {
    
}
