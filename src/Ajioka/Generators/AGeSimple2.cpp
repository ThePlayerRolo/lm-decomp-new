#include "Ajioka/Generators/AGeSimple2.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[5] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0_Init, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0_Behavior
    },
    
    {
        STRAT_STATE_104, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x104_Init, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x104_Behavior
    },

    {
        STRAT_STATE_103, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x103_Init, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x103_Behavior
    },


    {
        STRAT_STATE_106, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x106_Init, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x106_Behavior
    },

    {
        STRAT_STATE_107, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x107_Init, 
        (EnemyStrategyStateFn)&AGeSimple2::state_0x107_Behavior
    },
};

AGeSimple2::AGeSimple2() {}
AGeSimple2::~AGeSimple2() {}
void AGeSimple2::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AGeSimple2::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}
void AGeSimple2::receiveMessage(GeneratorEvent* msg) {}
bool AGeSimple2::state_0_Init() { return true; }
bool AGeSimple2::state_0_Behavior() { return true; }
bool AGeSimple2::state_0x104_Init() { return true; }
bool AGeSimple2::state_0x104_Behavior() { return true; }
bool AGeSimple2::state_0x103_Init() { return true; }
bool AGeSimple2::state_0x103_Behavior() { return true; }
bool AGeSimple2::state_0x106_Init() { return true; }
bool AGeSimple2::state_0x106_Behavior() { return true; }
bool AGeSimple2::state_0x107_Init() { return true; }
bool AGeSimple2::state_0x107_Behavior() { return true; }
