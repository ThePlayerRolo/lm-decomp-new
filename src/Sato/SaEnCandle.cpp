#include "Sato/SaEnCandle.hpp"
#include "Koga/CharacterEventObserver.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0x1] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&SaEnCandle::state_0_Init, 
        (EnemyStrategyStateFn)&SaEnCandle::state_0_Behavior
    },
};

SaEnCandle::SaEnCandle(): Koga::CharacterEvent(Koga::CharacterEvent::MESSAGE_TRUE) {}
SaEnCandle::~SaEnCandle() {}
void SaEnCandle::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void SaEnCandle::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}
bool SaEnCandle::state_0_Init() { return true; }
bool SaEnCandle::state_0_Behavior() { return true; }
bool SaEnCandle::onCaptureBegin(Koga::CharacterEvent* msg) { return true; }
bool SaEnCandle::onCaptureEnd(Koga::CharacterEvent* msg) { return true; }
