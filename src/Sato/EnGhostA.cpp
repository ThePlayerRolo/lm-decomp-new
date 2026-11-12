#include "Sato/EnGhostA.hpp"
#include "Sato/EnRotation.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0xC] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&EnGhostA::state_0_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_0_Behavior
    },

    {
        STRAT_STATE_B, 
        (EnemyStrategyStateFn)&EnGhostA::state_B_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_B_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&EnGhostA::state_1_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&EnGhostA::state_2_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&EnGhostA::state_3_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&EnGhostA::state_4_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&EnGhostA::state_5_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_5_Behavior
    },

    {
        STRAT_STATE_6, 
        (EnemyStrategyStateFn)&EnGhostA::state_6_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_6_Behavior
    },

    {
        STRAT_STATE_7, 
        (EnemyStrategyStateFn)&EnGhostA::state_7_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_7_Behavior
    },

    {
        STRAT_STATE_8, 
        (EnemyStrategyStateFn)&EnGhostA::state_8_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_8_Behavior
    },

    {
        STRAT_STATE_9, 
        (EnemyStrategyStateFn)&EnGhostA::state_9_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_9_Behavior
    },

    {
        STRAT_STATE_A, 
        (EnemyStrategyStateFn)&EnGhostA::state_A_Init, 
        (EnemyStrategyStateFn)&EnGhostA::state_A_Behavior
    },
};

EnGhostA::EnGhostA() {

}


EnRotationFar::~EnRotationFar() {

}

EnRotationNear::~EnRotationNear() {
    
}



void EnGhostA::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void EnGhostA::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool EnGhostA::vt_14() {
    return false;
}


bool EnGhostA::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onSprayedWithFire(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onSprayedWithIce(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onSprayedWithWater(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onEnteredFlashlightBeam(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::vt_18(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onFishingBegin(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onCaptureBegin(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::onPlayerEnteredRoom(Koga::CharacterEvent* msg) {
    return true;
}

bool EnGhostA::state_0_Init() {
    return true;
}

bool EnGhostA::state_0_Behavior() {
    return true;
}

bool EnGhostA::state_1_Init() {
    return true;
}

bool EnGhostA::state_1_Behavior() {
    return true;
}

bool EnGhostA::state_2_Init() {
    return true;
}

bool EnGhostA::state_2_Behavior() {
    return true;
}

bool EnGhostA::state_3_Init() {
    return true;
}

bool EnGhostA::state_3_Behavior() {
    return true;
}

bool EnGhostA::state_4_Init() {
    return true;
}

bool EnGhostA::state_4_Behavior() {
    return true;
}

bool EnGhostA::state_5_Init() {
    return true;
}

bool EnGhostA::state_5_Behavior() {
    return true;
}

bool EnGhostA::state_6_Init() {
    return true;
}

bool EnGhostA::state_6_Behavior() {
    return true;
}

bool EnGhostA::state_7_Init() {
    return true;
}

bool EnGhostA::state_7_Behavior() {
    return true;
}

bool EnGhostA::state_8_Init() {
    return true;
}

bool EnGhostA::state_8_Behavior() {
    return true;
}

bool EnGhostA::state_9_Init() {
    return true;
}

bool EnGhostA::state_9_Behavior() {
    return true;
}

bool EnGhostA::state_A_Init() {
    return true;
}

bool EnGhostA::state_A_Behavior() {
    return true;
}

bool EnGhostA::state_B_Init() {
    return true;
}

bool EnGhostA::state_B_Behavior() {
    return true;
}

void EnGhostA::EnGhostA_fn_800C8EC0() {

}

void EnGhostA::EnGhostA_fn_800C8ECC() {

}

void EnGhostA::EnGhostA_fn_800C8F28() {

}

void EnGhostA::EnGhostA_fn_800C8F54() {

}

bool EnGhostA::EnGhostA_fn_800C8F88() {
    return false;
}

bool EnGhostA::EnGhostA_fn_800C8FB8() {
    return true;
}

void EnGhostA::EnGhostA_fn_800C8FE8() {

}

void EnGhostA::EnGhostA_fn_800C902C() {

}

EnGhostA::~EnGhostA() {
    
}
