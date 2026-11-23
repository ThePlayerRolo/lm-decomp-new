#include "Ajioka/Generators/AGeHideSeek.hpp"
#include "Koga/GeneratorEvent.hpp"
#include "Koga/EnemyGenManager.hpp"
#include "Sato/EnThought.hpp"
#include "Unsorted/AssortedEnManager.hpp"
#include "Unsorted/InGameFlagsUtil.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

void fn_800209EC(s32);

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

static s32 lbl_8036D6DC[5] = {
    124, 125, 126, 127, 128
};

AGeHideSeek::AGeHideSeek() : _19(0) {}
AGeHideSeek::~AGeHideSeek() {
    if (_19 != 0) {
        _19 = 0;
        fn_800209EC(4);
    }
}

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

void AGeHideSeek::receiveMessage(GeneratorEvent* pMsg) {
    GeneratorEvent::Message msg = pMsg->mMessage;

    switch (msg) {
        case GeneratorEvent::MESSAGE_1:
            for (int i = 0; i < 7; i++) {
                if (_30[i] == pMsg->mThought->getStrategy()) {
                    _30[i] = nullptr;
                }
            }
        break;
        case GeneratorEvent::MESSAGE_0:
            pMsg->_8[lbl_8036D6DC[0]] = 1;
            pMsg->_8[lbl_8036D6DC[1]] = 1;
            pMsg->_8[lbl_8036D6DC[2]] = 1;
            pMsg->_8[lbl_8036D6DC[3]] = 1;
            pMsg->_8[lbl_8036D6DC[4]] = 1;
            break;
        default:
            break;
    }

}

// https://decomp.me/scratch/eJQnx
bool AGeHideSeek::state_0_Init() {
    mEnabledFlag = FLAG_TWIN_HIDE_SEEK_ENABLED;
    _19 = 0;

    Koga::ToolData* path = static_cast<EnemyGenerator*>(mpUserData)->getGenPath();
    ToolDataRef data = static_cast<EnemyGenerator*>(mpUserData)->fn_800C2784();

    data.getToolData()->getValue(data.mEntryIndex, "pos_x", &mGeneratorPos.x);
    data.getToolData()->getValue(data.mEntryIndex, "pos_y", &mGeneratorPos.y);
    data.getToolData()->getValue(data.mEntryIndex, "pos_z", &mGeneratorPos.z);

    for (int i =  0; i < 7; i++) {
        _30[i] = nullptr;
    }

    static_cast<EnemyGenerator*>(mpUserData)->_870 |= 1;
    setNextState(1);
    return true;
}

bool AGeHideSeek::state_0_Behavior() { return true; }
bool AGeHideSeek::state_1_Init() { return true; }

bool AGeHideSeek::state_1_Behavior() {
    if (getFlagValue(mEnabledFlag)) {
        u32 uVar1 = fn_80017ADC(mGeneratorPos, -1);
        // todo: needs to struct not decompiled yet
    }

    return true;
}

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
