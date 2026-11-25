#include "Sato/SaEnKoopaTelesa.hpp"
#include "Koga/CharacterEventObserver.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0x6] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_0_Init, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_1_Init, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_2_Init, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_3_Init, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_3_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_5_Init, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_5_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_4_Init, 
        (EnemyStrategyStateFn)&SaEnKoopaTelesa::state_4_Behavior
    },
};

SaEnKoopaTelesa::SaEnKoopaTelesa() : Koga::CharacterEvent(Koga::CharacterEvent::MESSAGE_TRUE) {}
SaEnKoopaTelesa::~SaEnKoopaTelesa() {}

void SaEnKoopaTelesa::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void SaEnKoopaTelesa::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }    
}

bool SaEnKoopaTelesa::state_0_Init(){ return true; }
bool SaEnKoopaTelesa::state_0_Behavior(){ return true; }
bool SaEnKoopaTelesa::state_2_Init(){ return true; }
bool SaEnKoopaTelesa::state_2_Behavior(){ return true; }
bool SaEnKoopaTelesa::state_5_Init(){ return true; }
bool SaEnKoopaTelesa::state_5_Behavior(){ return true; }
bool SaEnKoopaTelesa::state_1_Init(){ return true; }
bool SaEnKoopaTelesa::state_1_Behavior(){ return true; }
bool SaEnKoopaTelesa::state_3_Init(){ return true; }
bool SaEnKoopaTelesa::state_3_Behavior(){ return true; }
bool SaEnKoopaTelesa::state_4_Init(){ return true; }
bool SaEnKoopaTelesa::state_4_Behavior(){ return true; }

void SaEnKoopaTelesa::vt_08(){}
void SaEnKoopaTelesa::SaEnTelesaBase_vt_0F(){}
void SaEnKoopaTelesa::SaEnTelesaBase_vt_14(){}

bool SaEnKoopaTelesa::vt_14() { return true; }
bool SaEnKoopaTelesa::onCaptureEnd(Koga::CharacterEvent* msg) { return true; }
bool SaEnKoopaTelesa::onCaptureBegin(Koga::CharacterEvent* msg) { return true; }
bool SaEnKoopaTelesa::onCollideWithPlayer(CharacterEvent* msg) { return true; }
