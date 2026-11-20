#include "Sato/EnHeyMask.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStatesMask[6] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&EnHeyMask::state_0_Init, 
        (EnemyStrategyStateFn)&EnHeyMask::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&EnHeyMask::state_1_Init, 
        (EnemyStrategyStateFn)&EnHeyMask::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&EnHeyMask::state_2_Init, 
        (EnemyStrategyStateFn)&EnHeyMask::state_2_Behavior
    }, 

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&EnHeyMask::state_3_Init, 
        (EnemyStrategyStateFn)&EnHeyMask::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&EnHeyMask::state_4_Init, 
        (EnemyStrategyStateFn)&EnHeyMask::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&EnHeyMask::state_5_Init, 
        (EnemyStrategyStateFn)&EnHeyMask::state_5_Behavior
    },
};


static EnemyStrategyState enemiesStatesZenmai[2] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&EnZenmai::state_0_Init, 
        (EnemyStrategyStateFn)&EnZenmai::state_0_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&EnZenmai::state_4_Init, 
        (EnemyStrategyStateFn)&EnZenmai::state_4_Behavior
    },
};


void EnHeyMask::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesMask, ARRAY_COUNT(enemiesStatesMask), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void EnHeyMask::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesMask, ARRAY_COUNT(enemiesStatesMask), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

void EnHeyMask::vt_08() {

}

bool EnHeyMask::state_0_Init() {
    return true;
}

bool EnHeyMask::state_0_Behavior() {
    return true;
}

bool EnHeyMask::state_1_Init() {
    return true;
}

bool EnHeyMask::state_1_Behavior() {
    return true;
}

bool EnHeyMask::state_2_Init() {
    return true;
}

bool EnHeyMask::state_2_Behavior() {
    return true;
}

bool EnHeyMask::state_4_Init() {
    return true;
}

bool EnHeyMask::state_4_Behavior() {
    return true;
}

bool EnHeyMask::state_3_Init() {
    return true;
}

bool EnHeyMask::state_3_Behavior() {
    return true;
}

bool EnHeyMask::state_5_Init() {
    return true;
}

bool EnHeyMask::state_5_Behavior() {
    return true;
}


void EnHeyMask::EnHeyMask_fn_800C6270() {

}

void EnHeyMask::EnHeyMask_fn_800C62DC() {

}

void EnZenmai::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesZenmai, ARRAY_COUNT(enemiesStatesZenmai), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void EnZenmai::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesZenmai, ARRAY_COUNT(enemiesStatesZenmai), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}


bool EnZenmai::state_0_Init() {
    return true;
}

bool EnZenmai::state_0_Behavior() {
    return true;
}

bool EnZenmai::state_4_Init() {
    return true;
}

bool EnZenmai::state_4_Behavior() {
    return false;
}


void EnZenmai::EnHeyMask_fn_800C6270() {

}

void EnZenmai::EnHeyMask_fn_800C62DC() {

}



void EnHeySpear::doBehavior() {

}
