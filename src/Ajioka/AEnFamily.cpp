#include "Ajioka/AEnFamily.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0x12] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnFamily::state_0_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnFamily::state_1_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnFamily::state_2_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnFamily::state_3_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnFamily::state_4_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnFamily::state_5_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_5_Behavior
    },

    {
        STRAT_STATE_6, 
        (EnemyStrategyStateFn)&AEnFamily::state_6_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_6_Behavior
    },

    {
        STRAT_STATE_7, 
        (EnemyStrategyStateFn)&AEnFamily::state_7_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_7_Behavior
    },

    {
        STRAT_STATE_8, 
        (EnemyStrategyStateFn)&AEnFamily::state_8_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_8_Behavior
    },

    {
        STRAT_STATE_9, 
        (EnemyStrategyStateFn)&AEnFamily::state_9_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_9_Behavior
    },

    {
        STRAT_STATE_A, 
        (EnemyStrategyStateFn)&AEnFamily::state_A_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_A_Behavior
    },
    

    {
        STRAT_STATE_B, 
        (EnemyStrategyStateFn)&AEnFamily::state_B_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_B_Behavior
    },
    

    {
        STRAT_STATE_C, 
        (EnemyStrategyStateFn)&AEnFamily::state_C_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_C_Behavior
    },
    

    {
        STRAT_STATE_D, 
        (EnemyStrategyStateFn)&AEnFamily::state_D_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_D_Behavior
    },
    

    {
        STRAT_STATE_E, 
        (EnemyStrategyStateFn)&AEnFamily::state_E_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_E_Behavior
    },
    

    {
        STRAT_STATE_F, 
        (EnemyStrategyStateFn)&AEnFamily::state_F_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_F_Behavior
    },
    

    {
        STRAT_STATE_10, 
        (EnemyStrategyStateFn)&AEnFamily::state_0x10_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_0x10_Behavior
    },
    

    {
        STRAT_STATE_11, 
        (EnemyStrategyStateFn)&AEnFamily::state_0x11_Init, 
        (EnemyStrategyStateFn)&AEnFamily::state_0x11_Behavior
    },
};

AEnFamily::AEnFamily() {}

AEnFamily::~AEnFamily() {}


void AEnFamily::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnFamily::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnFamily::vt_14() {
    return true;
}



bool AEnFamily::state_0_Init() {
    return true;
}

bool AEnFamily::state_0_Behavior() {
    return true;
}

bool AEnFamily::state_1_Init() {
    return true;
}

bool AEnFamily::state_1_Behavior() {
    return true;
}

bool AEnFamily::state_2_Init() {
    return true;
}

bool AEnFamily::state_2_Behavior() {
    return true;
}

bool AEnFamily::state_3_Init() {
    return true;
}

bool AEnFamily::state_3_Behavior() {
    return true;
}

bool AEnFamily::state_4_Init() {
    return true;
}

bool AEnFamily::state_4_Behavior() {
    return true;
}

bool AEnFamily::state_5_Init() {
    return true;
}

bool AEnFamily::state_5_Behavior() {
    return true;
}

bool AEnFamily::state_6_Init() {
    return true;
}

bool AEnFamily::state_6_Behavior() {
    return true;
}

bool AEnFamily::state_7_Init() {
    return true;
}

bool AEnFamily::state_7_Behavior() {
    return true;
}

bool AEnFamily::state_8_Init() {
    return true;
}

bool AEnFamily::state_8_Behavior() {
    return true;
}

bool AEnFamily::state_9_Init() {
    return true;
}

bool AEnFamily::state_9_Behavior() {
    return true;
}

bool AEnFamily::state_A_Init() {
    return true;
}

bool AEnFamily::state_A_Behavior() {
    return true;
}

bool AEnFamily::state_B_Init() {
    return true;
}

bool AEnFamily::state_B_Behavior() {
    return true;
}

bool AEnFamily::state_C_Init() {
    return true;
}

bool AEnFamily::state_C_Behavior() {
    return true;
}

bool AEnFamily::state_D_Init() {
    return true;
}

bool AEnFamily::state_D_Behavior() {
    return true;
}

bool AEnFamily::state_E_Init() {
    return true;
}

bool AEnFamily::state_E_Behavior() {
    return true;
}

bool AEnFamily::state_F_Init() {
    return true;
}

bool AEnFamily::state_F_Behavior() {
    return true;
}

bool AEnFamily::state_0x10_Init() {
    return true;
}

bool AEnFamily::state_0x10_Behavior() {
    return true;
}

bool AEnFamily::state_0x11_Init() {
    return true;
}

bool AEnFamily::state_0x11_Behavior() {
    return true;
}

bool AEnFamily::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnFamily::vt_18(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnFamily::onEnteredFlashlightBeam(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnFamily::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return true;
}


bool AEnFamily::onFishingBegin(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnFamily::onCaptureBegin(Koga::CharacterEvent* msg) {
    return true;
}
