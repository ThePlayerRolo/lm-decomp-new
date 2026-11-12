#include "Ajioka/Kagu/AEnKaguBase.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()


static s32 lbl_804D4110 = 0x32;
static s32 lbl_804D4114 = 0x05;
static s32 lbl_804D4118 = 0x64;
static char lbl_804D411C[] = "NORMAL";
static char lbl_804D4124[] = "OPEN";
static char lbl_804D412C[] = "CLOSE";

static EnemyStrategyState enemiesStates[4] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_0_Init, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_1_Init, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_1_Behavior
    },

    
    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_2_Init, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_2_Behavior
    },

    
    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_3_Init, 
        (EnemyStrategyStateFn)&AEnKaguBase::state_3_Behavior
    },
};

AEnKaguBase::AEnKaguBase() {
    m_24 = true;
    m_25 = true;
    m_26 = true;
    m_27 = true;
    m_18 = 0;
    m_28 = 0;
    m_1c = 0;
    m_20 = 0;
}


void AEnKaguBase::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnKaguBase::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnKaguBase::state_0_Init() {
    return true;
}

bool AEnKaguBase::state_0_Behavior() {
    return true;
}

bool AEnKaguBase::state_1_Init() {
    return true;
}

bool AEnKaguBase::state_1_Behavior() {
    return true;
}

bool AEnKaguBase::state_2_Init() {
    return true;
}

bool AEnKaguBase::state_2_Behavior() {
    return true;
}

bool AEnKaguBase::state_3_Init() {
    return true;
}

bool AEnKaguBase::state_3_Behavior() {
    return true;
}


// Koga::CharacterEventObserver
bool AEnKaguBase::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnKaguBase::onSprayedWithWater(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnKaguBase::onSprayedWithFire(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnKaguBase::onSprayedWithIce(Koga::CharacterEvent* msg) {
    return true;
}


bool AEnKaguBase::onPlayerTapped(Koga::CharacterEvent* msg) {
    return true;
}

bool AEnKaguBase::isCurrentState2() {
    return mCurrentState == 2;
}

void AEnKaguBase::fn_800F66E8() {

}

void AEnKaguBase::fn_800F6724() {

}

void AEnKaguBase::fn_800F6754() {

}

void AEnKaguBase::fn_800F6778() {

}

void AEnKaguBase::fn_800F6784() {

}
