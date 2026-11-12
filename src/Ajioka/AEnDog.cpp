#include "Ajioka/AEnDog.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0x14] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnDog::state_0_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnDog::state_1_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnDog::state_2_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnDog::state_3_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnDog::state_4_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnDog::state_5_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_5_Behavior
    },

    {
        STRAT_STATE_6, 
        (EnemyStrategyStateFn)&AEnDog::state_6_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_6_Behavior
    },

    {
        STRAT_STATE_7, 
        (EnemyStrategyStateFn)&AEnDog::state_7_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_7_Behavior
    },

    {
        STRAT_STATE_8, 
        (EnemyStrategyStateFn)&AEnDog::state_8_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_8_Behavior
    },

    {
        STRAT_STATE_9, 
        (EnemyStrategyStateFn)&AEnDog::state_9_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_9_Behavior
    },

    {
        STRAT_STATE_A, 
        (EnemyStrategyStateFn)&AEnDog::state_A_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_A_Behavior
    },
    

    {
        STRAT_STATE_B, 
        (EnemyStrategyStateFn)&AEnDog::state_B_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_B_Behavior
    },
    

    {
        STRAT_STATE_C, 
        (EnemyStrategyStateFn)&AEnDog::state_C_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_C_Behavior
    },
    

    {
        STRAT_STATE_D, 
        (EnemyStrategyStateFn)&AEnDog::state_D_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_D_Behavior
    },
    

    {
        STRAT_STATE_E, 
        (EnemyStrategyStateFn)&AEnDog::state_E_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_E_Behavior
    },
    

    {
        STRAT_STATE_F, 
        (EnemyStrategyStateFn)&AEnDog::state_F_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_F_Behavior
    },
    

    {
        STRAT_STATE_10, 
        (EnemyStrategyStateFn)&AEnDog::state_0x10_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_0x10_Behavior
    },
    

    {
        STRAT_STATE_11, 
        (EnemyStrategyStateFn)&AEnDog::state_0x11_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_0x11_Behavior
    },

    {
        STRAT_STATE_12, 
        (EnemyStrategyStateFn)&AEnDog::state_0x12_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_0x12_Behavior
    },

    {
        STRAT_STATE_13, 
        (EnemyStrategyStateFn)&AEnDog::state_0x13_Init, 
        (EnemyStrategyStateFn)&AEnDog::state_0x13_Behavior
    },
};

AEnDog::AEnDog() {

}


void AEnDog::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnDog::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnDog::vt_14() {
    return true;
}

bool AEnDog::state_0_Init() {
    return true;
}

bool AEnDog::state_0_Behavior() {
    return true;
}

bool AEnDog::state_1_Init() {
    return true;
}

bool AEnDog::state_1_Behavior() {
    return true;
}

bool AEnDog::state_2_Init() {
    return true;
}

bool AEnDog::state_2_Behavior() {
    return true;
}

bool AEnDog::state_3_Init() {
    return true;
}

bool AEnDog::state_3_Behavior() {
    return true;
}

bool AEnDog::state_4_Init() {
    return true;
}

bool AEnDog::state_4_Behavior() {
    return true;
}

bool AEnDog::state_5_Init() {
    return true;
}

bool AEnDog::state_5_Behavior() {
    return true;
}

bool AEnDog::state_6_Init() {
    return true;
}

bool AEnDog::state_6_Behavior() {
    return true;
}

bool AEnDog::state_7_Init() {
    return true;
}

bool AEnDog::state_7_Behavior() {
    return true;
}

bool AEnDog::state_8_Init() {
    return true;
}

bool AEnDog::state_8_Behavior() {
    return true;
}

bool AEnDog::state_9_Init() {
    return true;
}

bool AEnDog::state_9_Behavior() {
    return true;
}

bool AEnDog::state_A_Init() {
    return true;
}

bool AEnDog::state_A_Behavior() {
    return true;
}

bool AEnDog::state_B_Init() {
    return true;
}

bool AEnDog::state_B_Behavior() {
    return true;
}

bool AEnDog::state_C_Init() {
    return true;
}

bool AEnDog::state_C_Behavior() {
    return true;
}

bool AEnDog::state_D_Init() {
    return true;
}

bool AEnDog::state_D_Behavior() {
    return true;
}

bool AEnDog::state_E_Init() {
    return true;
}

bool AEnDog::state_E_Behavior() {
    return true;
}

bool AEnDog::state_F_Init() {
    return true;
}

bool AEnDog::state_F_Behavior() {
    return true;
}

bool AEnDog::state_0x10_Init() {
    return true;
}

bool AEnDog::state_0x10_Behavior() {
    return true;
}

bool AEnDog::state_0x11_Init() {
    return true;
}

bool AEnDog::state_0x11_Behavior() {
    return true;
}

bool AEnDog::state_0x12_Init() {
    return true;
}

bool AEnDog::state_0x12_Behavior() {
    return true;
}

bool AEnDog::state_0x13_Init() {
    return true;
}

bool AEnDog::state_0x13_Behavior() {
    return true;
}


bool AEnDog::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnDog::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnDog::onFishingBegin(Koga::CharacterEvent* msg) {
    return true;
}


AEnDog::~AEnDog() {
    
}
