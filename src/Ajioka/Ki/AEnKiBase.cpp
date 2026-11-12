#include "Ajioka/Ki/AEnKiBase.hpp"
#include "JSystem/JAudio/JAInterface/JAIAnimation.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static char lbl_804D41A0[] = "ENDING";

static EnemyStrategyState enemiesStates[5] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnKiBase::state_0_Init, 
        (EnemyStrategyStateFn)&AEnKiBase::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnKiBase::state_1_Init, 
        (EnemyStrategyStateFn)&AEnKiBase::state_1_Behavior
    },

    
    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnKiBase::state_2_Init, 
        (EnemyStrategyStateFn)&AEnKiBase::state_2_Behavior
    },

    
    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnKiBase::state_3_Init, 
        (EnemyStrategyStateFn)&AEnKiBase::state_3_Behavior
    },
    
    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnKiBase::state_4_Init, 
        (EnemyStrategyStateFn)&AEnKiBase::state_4_Behavior
    },
};


int lbl_80366B9C[] = {1, 2, 3};
int lbl_80366BA8[] = {4, 5, 6};

AEnKiBase::AEnKiBase() {
    m_18 = 0;
    for (int i = 0; i < 32; i++) {
        m_1c[i] = 0;
    }
}

void AEnKiBase::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnKiBase::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}


bool AEnKiBase::vt_14() {
    return false;
}

bool AEnKiBase::state_0_Init() {
    return true;
}

bool AEnKiBase::state_0_Behavior() {
    return true;
}

bool AEnKiBase::state_1_Init() {
    return true;
}

bool AEnKiBase::state_1_Behavior() {
    return true;
}

bool AEnKiBase::state_2_Init() {
    return true;
}

bool AEnKiBase::state_2_Behavior() {
    return true;
}

bool AEnKiBase::state_3_Init() {
    return true;
}

bool AEnKiBase::state_3_Behavior() {
    return true;
}

bool AEnKiBase::state_4_Init() {
    return true;
}

bool AEnKiBase::state_4_Behavior() {
    return true;
}


AEnKiBase::~AEnKiBase() {}
