#include "Ajioka/Zako/AEnZakoBase.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "macros.h"

dummy_float_data();
enemies_float_data();

static EnemyStrategyState enemiesStates[2] = {
    { 
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnZakoBase::state_0_Init, 
        (EnemyStrategyStateFn)&AEnZakoBase::state_0_Behavior
    },

    { 
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnZakoBase::state_1_Init, 
        (EnemyStrategyStateFn)&AEnZakoBase::state_1_Behavior
    },
};

AEnZakoBase::AEnZakoBase() {

}

// From EnemyStrategy
void AEnZakoBase::init() {

}

void AEnZakoBase::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnZakoBase::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }  
}

bool AEnZakoBase::vt_14() {
    return true;
}

bool AEnZakoBase::state_0_Init() {
    return true;
}

bool AEnZakoBase::state_0_Behavior() {
    return true;
}

bool AEnZakoBase::state_1_Init() {
    return true;
}

bool AEnZakoBase::state_1_Behavior() {
    return true;
}


// From this class
void AEnZakoBase::AEnZakoBase_fn_800F5CB8() {}

void AEnZakoBase::vt_08() {
    return;
}

// From Koga::CharacterEventObserver
bool AEnZakoBase::onPlayerLeftRoom(Koga::CharacterEvent* msg){
    return true;
}

bool AEnZakoBase::onCollideWithPlayer(Koga::CharacterEvent* msg){
    return true;
}

bool AEnZakoBase::onSprayedWithWater(Koga::CharacterEvent* msg){
    return true;
}

bool AEnZakoBase::onSprayedWithFire(Koga::CharacterEvent* msg){
    return true;
}

bool AEnZakoBase::onSprayedWithIce(Koga::CharacterEvent* msg){
    return true;
}

// From this class
void AEnZakoBase::AEnZakoBase_fn_800F5F4C() {

}

void AEnZakoBase::AEnZakoBase_fn_800F5FA8() {

}

void AEnZakoBase::AEnZakoBase_fn_800F6010() {

}

void AEnZakoBase::AEnZakoBase_fn_800F6048() {

}

void AEnZakoBase::AEnZakoBase_fn_800F6080() {

}

void AEnZakoBase::AEnZakoBase_fn_800F60B8() {

}
