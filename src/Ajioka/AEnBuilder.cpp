#include "Ajioka/AEnBuilder.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0xF] = {
    {
        0, 
        (EnemyStrategyStateFn)&AEnBuilder::state_0_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_0_Behavior
    },

    {
        1, 
        (EnemyStrategyStateFn)&AEnBuilder::state_1_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_1_Behavior
    },

    {
        2, 
        (EnemyStrategyStateFn)&AEnBuilder::state_2_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_2_Behavior
    },

    {
        3, 
        (EnemyStrategyStateFn)&AEnBuilder::state_3_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_3_Behavior
    },

    {
        4, 
        (EnemyStrategyStateFn)&AEnBuilder::state_4_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_4_Behavior
    },

    {
        5, 
        (EnemyStrategyStateFn)&AEnBuilder::state_5_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_5_Behavior
    },

    {
        6, 
        (EnemyStrategyStateFn)&AEnBuilder::state_6_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_6_Behavior
    },

    {
        7, 
        (EnemyStrategyStateFn)&AEnBuilder::state_7_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_7_Behavior
    },

    {
        8, 
        (EnemyStrategyStateFn)&AEnBuilder::state_8_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_8_Behavior
    },

    {
        9, 
        (EnemyStrategyStateFn)&AEnBuilder::state_9_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_9_Behavior
    },

    {
        0xA, 
        (EnemyStrategyStateFn)&AEnBuilder::state_A_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_A_Behavior
    },
    

    {
        0xB, 
        (EnemyStrategyStateFn)&AEnBuilder::state_B_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_B_Behavior
    },
    

    {
        0xC, 
        (EnemyStrategyStateFn)&AEnBuilder::state_C_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_C_Behavior
    },
    

    {
        0xD, 
        (EnemyStrategyStateFn)&AEnBuilder::state_D_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_D_Behavior
    },
    

    {
        0xE, 
        (EnemyStrategyStateFn)&AEnBuilder::state_E_Init, 
        (EnemyStrategyStateFn)&AEnBuilder::state_E_Behavior
    },   
};

AEnBuilder::AEnBuilder() {}

AEnBuilder::~AEnBuilder() {}

void AEnBuilder::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnBuilder::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnBuilder::vt_14() {
    return true;
}


bool AEnBuilder::state_0_Init() {
    return true;
}

bool AEnBuilder::state_0_Behavior() {
    return true;
}

bool AEnBuilder::state_1_Init() {
    return true;
}

bool AEnBuilder::state_1_Behavior() {
    return true;
}

bool AEnBuilder::state_2_Init() {
    return true;
}

bool AEnBuilder::state_2_Behavior() {
    return true;
}

bool AEnBuilder::state_3_Init() {
    return true;
}

bool AEnBuilder::state_3_Behavior() {
    return true;
}

bool AEnBuilder::state_4_Init() {
    return true;
}

bool AEnBuilder::state_4_Behavior() {
    return true;
}

bool AEnBuilder::state_5_Init() {
    return true;
}

bool AEnBuilder::state_5_Behavior() {
    return true;
}

bool AEnBuilder::state_6_Init() {
    return true;
}

bool AEnBuilder::state_6_Behavior() {
    return true;
}

bool AEnBuilder::state_7_Init() {
    return true;
}

bool AEnBuilder::state_7_Behavior() {
    return true;
}

bool AEnBuilder::state_8_Init() {
    return true;
}

bool AEnBuilder::state_8_Behavior() {
    return true;
}

bool AEnBuilder::state_9_Init() {
    return true;
}

bool AEnBuilder::state_9_Behavior() {
    return true;
}

bool AEnBuilder::state_A_Init() {
    return true;
}

bool AEnBuilder::state_A_Behavior() {
    return true;
}

bool AEnBuilder::state_B_Init() {
    return true;
}

bool AEnBuilder::state_B_Behavior() {
    return true;
}

bool AEnBuilder::state_C_Init() {
    return true;
}

bool AEnBuilder::state_C_Behavior() {
    return true;
}

bool AEnBuilder::state_D_Init() {
    return true;
}

bool AEnBuilder::state_D_Behavior() {
    return true;
}

bool AEnBuilder::state_E_Init() {
    return true;
}

bool AEnBuilder::state_E_Behavior() {
    return true;
}

bool AEnBuilder::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnBuilder::vt_18(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnBuilder::onEnteredFlashlightBeam(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnBuilder::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnBuilder::onFishingBegin(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnBuilder::onCaptureBegin(Koga::CharacterEvent* msg) {
    return true;
}
