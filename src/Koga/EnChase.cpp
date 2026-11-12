
#include "Koga/EnCircleMove.hpp"
#include "Koga/EnChase.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

// I'm assuming its CircleMove for now since the function is labelled before EnChase first functions
static EnemyStrategyState enemiesStatesCircleMove[1] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&EnCircleMove::state_0_Init, 
        (EnemyStrategyStateFn)&EnCircleMove::state_0_Behavior
    },
};

void EnCircleMove::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesCircleMove, ARRAY_COUNT(enemiesStatesCircleMove), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void EnCircleMove::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesCircleMove, ARRAY_COUNT(enemiesStatesCircleMove), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool EnCircleMove::state_0_Init() {
    return true;
}

bool EnCircleMove::state_0_Behavior() {
    return true;
}

EnChase::EnChase() {

}

EnCircleMove::~EnCircleMove() {
    
}

// EnChase
static EnemyStrategyState enemiesStatesChase[3] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&EnChase::state_0_Init, 
        (EnemyStrategyStateFn)&EnChase::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&EnChase::state_1_Init, 
        (EnemyStrategyStateFn)&EnChase::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&EnChase::state_2_Init, 
        (EnemyStrategyStateFn)&EnChase::state_2_Behavior
    },
};

void EnChase::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesChase, ARRAY_COUNT(enemiesStatesChase), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void EnChase::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStatesChase, ARRAY_COUNT(enemiesStatesChase), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool EnChase::state_0_Init() {
    return true;
}

bool EnChase::state_0_Behavior() {
    return true;
}

bool EnChase::state_1_Init() {
    return true;
}

bool EnChase::state_1_Behavior() {
    return true;
}

bool EnChase::state_2_Init() {
    return true;
}

bool EnChase::state_2_Behavior() {
    return true;
}
