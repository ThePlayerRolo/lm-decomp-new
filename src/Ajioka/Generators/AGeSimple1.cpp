#include "Ajioka/Generators/AGeSimple1.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[3] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0_Init, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0_Behavior
    },

    {
        STRAT_STATE_106, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x106_Init, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x106_Behavior
    },

    {
        STRAT_STATE_107, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x107_Init, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x107_Behavior
    },
};

AGeSimple1::AGeSimple1() {}
AGeSimple1::~AGeSimple1() {}

void AGeSimple1::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AGeSimple1::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

void AGeSimple1::receiveMessage(GeneratorEvent* msg) {}
bool AGeSimple1::state_0_Init() { return true; }
bool AGeSimple1::state_0_Behavior() { return true; }
bool AGeSimple1::state_0x106_Init() { return true; }
bool AGeSimple1::state_0x106_Behavior() { return true; }
bool AGeSimple1::state_0x107_Init() { return true; }
bool AGeSimple1::state_0x107_Behavior() { return true; }
