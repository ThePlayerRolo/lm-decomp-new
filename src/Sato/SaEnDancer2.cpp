#include "Sato/SaEnDancer2.hpp"
#include "Koga/CharacterEventObserver.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0x1] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&SaEnDancer2::state_0_Init, 
        (EnemyStrategyStateFn)&SaEnDancer2::state_0_Behavior
    },
};

SaEnDancer2::SaEnDancer2() : Koga::CharacterEvent(Koga::CharacterEvent::MESSAGE_TRUE) {}
SaEnDancer2::~SaEnDancer2() {}

void SaEnDancer2::doBehavior(){
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void SaEnDancer2::doBehaviorInit(){
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool SaEnDancer2::state_0_Init(){ return true; }
bool SaEnDancer2::state_0_Behavior(){ return true; }

bool SaEnDancer2::onCaptureBegin(CharacterEvent* msg){ return true; }
bool SaEnDancer2::onCaptureEnd(CharacterEvent* msg){ return true; }
