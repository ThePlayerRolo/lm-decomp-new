#include "Ajioka/Generators/AGeHideSeek.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[7] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_0_Init, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_0_Behavior
    },
    
    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_1_Init, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_2_Init, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_2_Behavior
    },


    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_3_Init, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_4_Init, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_4_Behavior
    },
    
    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_5_Init, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_5_Behavior
    },
    
    {
        STRAT_STATE_6, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_6_Init, 
        (EnemyStrategyStateFn)&AGeHideSeek::state_6_Behavior
    },
};

AGeHideSeek::AGeHideSeek() {}
AGeHideSeek::~AGeHideSeek() {}
void AGeHideSeek::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AGeHideSeek::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}
void AGeHideSeek::receiveMessage(GeneratorEvent* msg) { }
bool AGeHideSeek::state_0_Init() { return true; }
bool AGeHideSeek::state_0_Behavior() { return true; }
bool AGeHideSeek::state_1_Init() { return true; }
bool AGeHideSeek::state_1_Behavior() { return true; }
bool AGeHideSeek::state_2_Init() { return true; }
bool AGeHideSeek::state_2_Behavior() { return true; }
bool AGeHideSeek::state_3_Init() { return true; }
bool AGeHideSeek::state_3_Behavior() { return true; }
bool AGeHideSeek::state_4_Init() { return true; }
bool AGeHideSeek::state_4_Behavior() { return true; }
bool AGeHideSeek::state_5_Init() { return true; }
bool AGeHideSeek::state_5_Behavior() { return true; }
bool AGeHideSeek::state_6_Init() { return true; }
bool AGeHideSeek::state_6_Behavior() { return true; }
