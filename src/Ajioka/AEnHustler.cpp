#include "Ajioka/AEnHustler.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()


static EnemyStrategyState enemiesStates[12] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnHustler::state_0_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnHustler::state_1_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnHustler::state_2_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnHustler::state_3_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnHustler::state_4_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnHustler::state_5_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_5_Behavior
    },

    {
        STRAT_STATE_6, 
        (EnemyStrategyStateFn)&AEnHustler::state_6_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_6_Behavior
    },

    {
        STRAT_STATE_7, 
        (EnemyStrategyStateFn)&AEnHustler::state_7_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_7_Behavior
    },

    {
        STRAT_STATE_8, 
        (EnemyStrategyStateFn)&AEnHustler::state_8_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_8_Behavior
    },

    {
        STRAT_STATE_9, 
        (EnemyStrategyStateFn)&AEnHustler::state_9_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_9_Behavior
    },

    {
        STRAT_STATE_A, 
        (EnemyStrategyStateFn)&AEnHustler::state_A_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_A_Behavior
    },
    

    {
        STRAT_STATE_B, 
        (EnemyStrategyStateFn)&AEnHustler::state_B_Init, 
        (EnemyStrategyStateFn)&AEnHustler::state_B_Behavior
    },
};

AEnHustler::AEnHustler() {}

AEnHustler::~AEnHustler() {}


void AEnHustler::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnHustler::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnHustler::vt_14() {
    return true;
}



bool AEnHustler::state_0_Init() {
    return true;
}

bool AEnHustler::state_0_Behavior() {
    return true;
}

bool AEnHustler::state_1_Init() {
    return true;
}

bool AEnHustler::state_1_Behavior() {
    return true;
}

bool AEnHustler::state_2_Init() {
    return true;
}

bool AEnHustler::state_2_Behavior() {
    return true;
}

bool AEnHustler::state_3_Init() {
    return true;
}

bool AEnHustler::state_3_Behavior() {
    return true;
}

bool AEnHustler::state_4_Init() {
    return true;
}

bool AEnHustler::state_4_Behavior() {
    return true;
}

bool AEnHustler::state_5_Init() {
    return true;
}

bool AEnHustler::state_5_Behavior() {
    return true;
}

bool AEnHustler::state_6_Init() {
    return true;
}

bool AEnHustler::state_6_Behavior() {
    return true;
}

bool AEnHustler::state_7_Init() {
    return true;
}

bool AEnHustler::state_7_Behavior() {
    return true;
}

bool AEnHustler::state_8_Init() {
    return true;
}

bool AEnHustler::state_8_Behavior() {
    return true;
}

bool AEnHustler::state_9_Init() {
    return true;
}

bool AEnHustler::state_9_Behavior() {
    return true;
}

bool AEnHustler::state_A_Init() {
    return true;
}

bool AEnHustler::state_A_Behavior() {
    return true;
}

bool AEnHustler::state_B_Init() {
    return true;
}

bool AEnHustler::state_B_Behavior() {
    return true;
}

bool AEnHustler::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return false;
}


bool AEnHustler::vt_18(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnHustler::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnHustler::onFishingBegin(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnHustler::onEnteredFlashlightBeam(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnHustler::vt_48(Koga::CharacterEvent* msg) {
    return false;
}
