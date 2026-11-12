#include "Ajioka/AEnTwins.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[11] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnTwins::state_0_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnTwins::state_1_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnTwins::state_2_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnTwins::state_3_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnTwins::state_4_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnTwins::state_5_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_5_Behavior
    },

    {
        STRAT_STATE_6, 
        (EnemyStrategyStateFn)&AEnTwins::state_6_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_6_Behavior
    },

    {
        STRAT_STATE_7, 
        (EnemyStrategyStateFn)&AEnTwins::state_7_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_7_Behavior
    },

    {
        STRAT_STATE_8, 
        (EnemyStrategyStateFn)&AEnTwins::state_8_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_8_Behavior
    },

    {
        STRAT_STATE_9, 
        (EnemyStrategyStateFn)&AEnTwins::state_9_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_9_Behavior
    },

    {
        STRAT_STATE_A, 
        (EnemyStrategyStateFn)&AEnTwins::state_A_Init, 
        (EnemyStrategyStateFn)&AEnTwins::state_A_Behavior
    },
};

AEnTwins::AEnTwins() {}

void AEnTwins::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnTwins::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnTwins::vt_14() {
    return true;
}



bool AEnTwins::state_0_Init() {
    return false;
}

bool AEnTwins::state_0_Behavior() {
    return true;
}

bool AEnTwins::state_1_Init() {
    return false;
}

bool AEnTwins::state_1_Behavior() {
    return false;
}

bool AEnTwins::state_2_Init() {
    return false;
}

bool AEnTwins::state_2_Behavior() {
    return false;
}

bool AEnTwins::state_3_Init() {
    return false;
}

bool AEnTwins::state_3_Behavior() {
    return false;
}

bool AEnTwins::state_4_Init() {
    return false;
}

bool AEnTwins::state_4_Behavior() {
    return false;
}

bool AEnTwins::state_5_Init() {
    return false;
}

bool AEnTwins::state_5_Behavior() {
    return false;
}

bool AEnTwins::state_6_Init() {
    return false;
}

bool AEnTwins::state_6_Behavior() {
    return false;
}

bool AEnTwins::state_7_Init() {
    return false;
}

bool AEnTwins::state_7_Behavior() {
    return false;
}

bool AEnTwins::state_8_Init() {
    return false;
}

bool AEnTwins::state_8_Behavior() {
    return false;
}

bool AEnTwins::state_9_Init() {
    return false;
}

bool AEnTwins::state_9_Behavior() {
    return false;
}

bool AEnTwins::state_A_Init() {
    return true;
}

bool AEnTwins::state_A_Behavior() {
    return false;
}



bool AEnTwins::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnTwins::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnTwins::onFishingBegin(Koga::CharacterEvent* msg) {
    return false;
}

bool AEnTwins::onEnteredFlashlightBeam(Koga::CharacterEvent* msg) {
    return true;
}

AEnTwins::~AEnTwins() {}
