#include "Ajioka/Ki/AEnKiSentak.hpp"
#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static char lbl_804D41C0[] = "ENDING";

static EnemyStrategyState enemiesStates[4] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_0_Init, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_1_Init, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_1_Behavior
    },

    
    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_2_Init, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_2_Behavior
    },

    
    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_3_Init, 
        (EnemyStrategyStateFn)&AEnKiSentak::state_3_Behavior
    },
};

int lbl_80366D30[] = {1, 2, 3};

AEnKiSentak::AEnKiSentak() {
    m_18 = 0;
    for (int i = 0; i < 32; i++) {
        m_1c[i] = 0;
    }
}



void AEnKiSentak::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnKiSentak::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }    
}


bool AEnKiSentak::vt_14() {
    return false;
}

bool AEnKiSentak::state_0_Init() {
    return true;
}

bool AEnKiSentak::state_0_Behavior() {
    return true;
}

bool AEnKiSentak::state_1_Init() {
    return true;
}

bool AEnKiSentak::state_1_Behavior() {
    return true;
}

bool AEnKiSentak::state_2_Init() {
    return true;
}

bool AEnKiSentak::state_2_Behavior() {
    return true;
}

bool AEnKiSentak::state_3_Init() {
    return true;
}

bool AEnKiSentak::state_3_Behavior() {
    return true;
}

bool AEnKiSentak::vt_48(Koga::CharacterEvent* msg) {
    return true;
}


AEnKiSentak::~AEnKiSentak() {}
