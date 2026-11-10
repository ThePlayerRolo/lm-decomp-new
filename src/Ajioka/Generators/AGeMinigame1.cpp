#include "Ajioka/Generators/AGeMinigame1.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[5] = {
    {
        0, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0_Init, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0_Behavior
    },
    
    {
        0x104, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x104_Init, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x104_Behavior
    },

    {
        0x103, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x103_Init, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x103_Behavior
    },


    {
        0x106, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x106_Init, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x106_Behavior
    },

    {
        0x107, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x107_Init, 
        (EnemyStrategyStateFn)&AGeMinigame1::state_0x107_Behavior
    },
};

AGeMinigame1::AGeMinigame1() {}
AGeMinigame1::~AGeMinigame1() {}
void AGeMinigame1::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AGeMinigame1::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}
void AGeMinigame1::receiveMessage(GeneratorEvent* msg) { }
bool AGeMinigame1::state_0_Init() { return true; }
bool AGeMinigame1::state_0_Behavior() { return true; }
bool AGeMinigame1::state_0x104_Init() { return true; }
bool AGeMinigame1::state_0x104_Behavior() { return true; }
bool AGeMinigame1::state_0x103_Init() { return true; }
bool AGeMinigame1::state_0x103_Behavior() { return true; }
bool AGeMinigame1::state_0x106_Init() { return true; }
bool AGeMinigame1::state_0x106_Behavior() { return true; }
bool AGeMinigame1::state_0x107_Init() { return true; }
bool AGeMinigame1::state_0x107_Behavior() { return true; }
