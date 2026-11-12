#include "Ajioka/Attack/AEnAtUpper.hpp"
#include "Ajioka/Attack/AEnAtStructs.hpp"
#include "JSystem/JGeometry/JGVec3.hpp"


dummy_float_data()
enemies_float_data()

static EnemyStrategyState enemiesStates[9] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_1_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_2_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_3_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_3_Behavior
    },

    {
        STRAT_STATE_4, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_4_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_4_Behavior
    },

    {
        STRAT_STATE_5, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_5_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_5_Behavior
    },

    {
        STRAT_STATE_102, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0x102_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0x102_Behavior
    },

    {
        STRAT_STATE_100, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0x100_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0x100_Behavior
    },

    {
        STRAT_STATE_101, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0x101_Init, 
        (EnemyStrategyStateFn)&AEnAtUpper::state_0x101_Behavior
    },
};

float data_float[] = { -10.f, 0.f, 35.f, -10.f, 0.f, -35.f };

static const AEnAtStruct1 mStruct1[] = {
    { 100.0f, 100.0f, { 0.0f, -50.0f, 0.0f} },
};

static const AEnAtStruct2 mStruct2 = { 1, mStruct1, 0 };

AEnAtUpper::AEnAtUpper() {
    _18 = &mStruct2;
}

char aEnAtUpperPath[] = "/param/th/AEnAtUpper.prm";
char kamaeru2[] = "KAMAERU2";

void AEnAtUpper::doBehavior() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void AEnAtUpper::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(enemiesStates, ARRAY_COUNT(enemiesStates), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool AEnAtUpper::vt_14() {
    return true;
}

bool AEnAtUpper::state_0_Init() {
    return false;
}

bool AEnAtUpper::state_0_Behavior() {
    return true;
}

bool AEnAtUpper::state_1_Init() {
    return true;
}

bool AEnAtUpper::state_1_Behavior() {
    return false;
}

bool AEnAtUpper::state_2_Init() {
    return false;
}

bool AEnAtUpper::state_2_Behavior() {
    return false;
}

bool AEnAtUpper::state_3_Init() {
    return false;
}

bool AEnAtUpper::state_3_Behavior() {
    return false;
}

bool AEnAtUpper::state_4_Init() {
    return false;
}

bool AEnAtUpper::state_4_Behavior() {
    return false;
}

bool AEnAtUpper::state_5_Init() {
    return true;
}

bool AEnAtUpper::state_5_Behavior() {
    return false;
}

bool AEnAtUpper::state_0x102_Init() {
    return true;
}

bool AEnAtUpper::state_0x102_Behavior() {
    return true;
}

bool AEnAtUpper::state_0x100_Init() {
    return true;
}

bool AEnAtUpper::state_0x100_Behavior() {
    return true;
}

bool AEnAtUpper::state_0x101_Init() {
    return true;
}

bool AEnAtUpper::state_0x101_Behavior() {
    return true;
}


bool AEnAtUpper::onCollideWithPlayer(Koga::CharacterEvent* msg) {
    return false;
}
