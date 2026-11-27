#include "Sato/EnReplace.hpp"
#include "Koga/800E634C.hpp"
#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnZako.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "macros.h"
#include "System/MathUtils.hpp"

dummy_float_data();
enemies_float_data();

static int unk1 = 60;
static const Koga::CharacterEvent::Message message = Koga::CharacterEvent::MESSAGE_CAPTURE_END;

static EnemyStrategyState enemyStrategyStates[3] = {
    {
        0,
        (EnemyStrategyStateFn)&EnReplace::state_0000_Init, 
        (EnemyStrategyStateFn)&EnReplace::state_0000_Behavior
    },

    {
        1, 
        (EnemyStrategyStateFn)&EnReplace::state_0010_Init, 
        (EnemyStrategyStateFn)&EnReplace::state_0010_Behavior
    },

    {
        256, 
        (EnemyStrategyStateFn)&EnReplace::state_0100_Init, 
        (EnemyStrategyStateFn)&EnReplace::state_0100_Behavior
    },
};

inline EnemyStrategyState* findState(u16 index) {
    for (EnemyStrategyState* state = &enemyStrategyStates[0]; state != &enemyStrategyStates[ARRAY_COUNT(enemyStrategyStates)]; state++) {
        if (state->mStateIndex == index) {
            return state;
        }
    }

    return nullptr;
}

void EnReplace::doBehavior() {
    EnemyStrategyState* state = findState(mCurrentState);
    
    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void EnReplace::doBehaviorInit() {
    EnemyStrategyState* state = findState(mCurrentState);
    
    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool EnReplace::vt_14() {
    return false;
}

bool EnReplace::state_0000_Init() {
    getZako()->getCharacter()->_40 |= 0xC400;
    getZako()->getCharacter()->setE3andE7();

    return true;
}

bool EnReplace::state_0000_Behavior() { 
    getZako()->getCharacter()->fn_80067C30(&gZeroVec);

    Character* character = getZako()->getCharacter();

    if (mTimer < unk1) {
        return true;
    }

    if (fn_800E6ED0(getZako()) == 0) {
        Koga::CharacterEvent event = Koga::CharacterEvent(message);
        getZako()->fn_800C0F08(this, &event);
    }

    setNextState(1);

    return true;
}

bool EnReplace::state_0010_Init() { return true; }

bool EnReplace::state_0010_Behavior() {
    if (getZako()->fn_800C0E48(200.0f) >= 0) {
        return true;
    }

    setNextState(0x0100);

    return true;
}

bool EnReplace::state_0100_Init() { return true; }

bool EnReplace::state_0100_Behavior() { return true; }
