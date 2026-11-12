#include "Ajioka/Beam/AEnBeamBase.hpp"
#include "Ajioka/Zako/AEnZakoBase.hpp"
#include "macros.h"

static char lbl_804d4160[] = "FLY";

dummy_float_data();
enemies_float_data();

static EnemyStrategyState enemiesStates[2] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnBeamBase::state_0_Init, 
        (EnemyStrategyStateFn)&AEnBeamBase::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnBeamBase::state_1_Init, 
        (EnemyStrategyStateFn)&AEnBeamBase::state_1_Behavior
    },
};

AEnBeamBase::~AEnBeamBase() {

}

AEnBeamBase::AEnBeamBase() {
    m_1a8 = false;
    m_1a9 = true;
    m_1aa = true;
    m_1b0 = 0.f;
    m_1b4 = 0.f;
    m_1b8 = 0.f;
    m_1bc = 0.f;
    m_1ab = false;
    m_1ac = false;
    m_1cc = 0;
}

void AEnBeamBase::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnBeamBase::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnBeamBase::vt_14() {
    return false;
}

bool AEnBeamBase::state_0_Init() {
    if (m_1a8) return false;

    m_7c  = false;
    m_7d  = false;
    m_7f  = false;
    m_80  = false;
    m_81  = false;
    m_82  = false;
    m_b4  = false;

    return false;
}


bool AEnBeamBase::state_0_Behavior() {
    return true;
}

bool AEnBeamBase::state_1_Init() {
    return true;
}

bool AEnBeamBase::state_1_Behavior() {
    return false;
}




void AEnBeamBase::AEnBeamBase_fn_800F6DEC() {

}

void AEnBeamBase::AEnBeamBase_fn_800F6DF8() {

}


void AEnBeamBase::AEnZakoBase_fn_800F5F4C() {

}

void AEnBeamBase::AEnBeamBase_fn_800F6EE8() {

}

void AEnBeamBase::AEnZakoBase_fn_800F6010() {

}

void AEnBeamBase::AEnBeamBase_fn_800F700C() {

}

void AEnBeamBase::AEnBeamBase_fn_800F7120() {

}
