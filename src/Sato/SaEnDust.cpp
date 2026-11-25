#include "Sato/SaEnDust.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[0x2] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&SaEnDust::state_0_Init, 
        (EnemyStrategyStateFn)&SaEnDust::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&SaEnDust::state_1_Init, 
        (EnemyStrategyStateFn)&SaEnDust::state_1_Behavior
    },
};


SaEnDust::SaEnDust() : Koga::CharacterEvent(Koga::CharacterEvent::MESSAGE_TRUE) {}
SaEnDust::~SaEnDust() {}
void SaEnDust::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void SaEnDust::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}
bool SaEnDust::state_0_Init() { return true; }
bool SaEnDust::state_0_Behavior() { return true; }
bool SaEnDust::state_1_Init() { return true; }
bool SaEnDust::state_1_Behavior() { return true; }
