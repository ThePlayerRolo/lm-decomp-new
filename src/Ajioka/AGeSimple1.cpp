#include "Ajioka/AGeSimple1.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[3] = {
    {
        0, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0_Init, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0_Behavior
    },

    {
        0x106, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x106_Init, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x106_Behavior
    },

    {
        0x107, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x107_Init, 
        (EnemyStrategyStateFn)&AGeSimple1::state_0x107_Behavior
    },
};

inline EnemyStrategyState* findState(u16 index) {
    for (   
        EnemyStrategyState* state = &enemiesStates[0]; 
        state != &enemiesStates[ARRAY_COUNT(enemiesStates)];
        state++) {

        if (state->mStateIndex == index) {
            return state;
        }
    }

    return nullptr;
}

AGeSimple1::AGeSimple1() {}
AGeSimple1::~AGeSimple1() {}
void AGeSimple1::doBehavior() {
    EnemyStrategyState* state = findState(mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}
void AGeSimple1::doBehaviorInit() {
    EnemyStrategyState* state = findState(mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}
void AGeSimple1::SaEnGenUtility_vt08() {}
bool AGeSimple1::state_0_Init() { return true; }
bool AGeSimple1::state_0_Behavior() { return true; }
bool AGeSimple1::state_0x106_Init() { return true; }
bool AGeSimple1::state_0x106_Behavior() { return true; }
bool AGeSimple1::state_0x107_Init() { return true; }
bool AGeSimple1::state_0x107_Behavior() { return true; }
