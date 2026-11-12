#include "Sato/EnItems.hpp"

#include "macros.h"

dummy_float_data()
enemies_float_data()

// EnemyStrategy in EnItem ?
static EnemyStrategyState entityStruct[4] = {
    {
        STRAT_STATE_0, 
        (EnemyStrategyStateFn)&EnItem::state_0_Init, 
        (EnemyStrategyStateFn)&EnItem::state_0_Behavior
    },

    {
        STRAT_STATE_1, 
        (EnemyStrategyStateFn)&EnItem::state_1_Init, 
        (EnemyStrategyStateFn)&EnItem::state_1_Behavior
    },

    {
        STRAT_STATE_2, 
        (EnemyStrategyStateFn)&EnItem::state_2_Init, 
        (EnemyStrategyStateFn)&EnItem::state_2_Behavior
    },

    {
        STRAT_STATE_3, 
        (EnemyStrategyStateFn)&EnItem::state_3_Init, 
        (EnemyStrategyStateFn)&EnItem::state_3_Behavior
    }
};

EnItem::EnItem() {}
EnItem::~EnItem() {}

void EnItem::doBehavior() {
    EnemyStrategyState* state = findStrategyState(entityStruct, ARRAY_COUNT(entityStruct), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorFunc)();
    }
}

void EnItem::doBehaviorInit() {
    EnemyStrategyState* state = findStrategyState(entityStruct, ARRAY_COUNT(entityStruct), mCurrentState);

    if (state != nullptr) {
        (this->*state->mBehaviorInitFunc)();
    }
}

bool EnItem::onCaptureEnd(Koga::CharacterEvent* msg) {
    return false;
}

bool EnItem::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    return false;
}

bool EnItem::state_0_Init() { return true; }
bool EnItem::state_0_Behavior() { return true; }
bool EnItem::state_1_Init() { return true; }
bool EnItem::state_1_Behavior() { return true; }
bool EnItem::state_2_Init() { return true; }
bool EnItem::state_2_Behavior() { return true; }
bool EnItem::state_3_Init() { return true; }
bool EnItem::state_3_Behavior() { return true; }


void EnItem::EnItem_fn_800CFFD8() {}

void EnItem::EnItem_fn_800D00A8() {}

void EnItem::EnItem_fn_800D00AC() {}

void EnItem::EnItem_fn_800D00B0() {}

bool EnItem::EnItem_fn_800D00B4() { return false; }

///////////////////////////////

void EnItemThrowUp::EnItem_fn_800D00A8() {

}

void EnItemThrowUp::EnItem_fn_800D00AC() {

}

void EnItemThrowUp::EnItemThrowUp_fn_800D036C() {
    
}

///////////////////////////////

EnKey::EnKey() {}
EnFiniteItem::~EnFiniteItem() {}
bool EnKey::onCaptureEnd(Koga::CharacterEvent* msg) { return true; }
void EnKey::EnItem_fn_800CFFD8() {}
void EnKey::EnItem_fn_800D00A8() {}
void EnKey::EnItem_fn_800D00AC() {}
void EnKey::EnItemThrowUp_fn_800D036C() {}
void EnKey::EnItem_fn_800D00B0() {}
bool EnKey::EnFiniteItem_fn_800D1318() { return true; }

void EnMarioItem::EnItem_fn_800CFFD8() {}
void EnMarioItem::EnItem_fn_800D00A8() {}
void EnMarioItem::EnItem_fn_800D00AC() {}
void EnMarioItem::EnItemThrowUp_fn_800D036C() {}
void EnMarioItem::EnItem_fn_800D00B0() {}
bool EnMarioItem::EnFiniteItem_fn_800D1318() { return true; }

///////////////////////////////

void EnNegativeItem::EnItem_fn_800CFFD8() {}
void EnNegativeItem::EnItem_fn_800D00A8() {}
void EnNegativeItem::EnItem_fn_800D00AC() {}
void EnNegativeItem::EnItemThrowUp_fn_800D036C() {}
void EnNegativeItem::EnItem_fn_800D00B0() {}



EnFiniteItem::EnFiniteItem() {}
EnItemThrowUp::~EnItemThrowUp() {}


void EnFiniteItem::vt_08() {}
void EnFiniteItem::EnFiniteItem_fn_800D12E8() {}
void EnFiniteItem::EnFiniteItem_fn_800D1300() {}
bool EnFiniteItem::EnFiniteItem_fn_800D1318() { return false; }

///////////////////////////////

void EnHeartItem::init() {}
EnHeartItem::~EnHeartItem() {}
void EnHeartItem::EnItem_fn_800CFFD8() {}
void EnHeartItem::EnItem_fn_800D00A8() {}
void EnHeartItem::EnItem_fn_800D00AC() {}
void EnHeartItem::EnItemThrowUp_fn_800D036C() {}
void EnHeartItem::EnItem_fn_800D00B0() {}


///////////////////////////////

EnJewel::~EnJewel() {}
void EnJewel::EnItem_fn_800CFFD8() {}
void EnJewel::EnItem_fn_800D00B0() {}
void EnJewel::EnItem_fn_800D00A8() {}
void EnJewel::EnItem_fn_800D00AC() {}
void EnJewel::EnItemThrowUp_fn_800D036C() {}

///////////////////////////////

EnPearl::EnPearl() {}
void EnPearl::EnItem_fn_800CFFD8() {}
bool EnPearl::EnItem_fn_800D00B4() { return true; }


void EnGold::EnItem_fn_800CFFD8() {}
void EnGold::EnItemThrowUp_fn_800D036C() {}


EnElementJewel::EnElementJewel() {}
EnElementJewel::~EnElementJewel() {}
bool EnElementJewel::onCaptureEnd(Koga::CharacterEvent* msg) { return true; }
void EnElementJewel::EnItem_fn_800CFFD8() {}
void EnElementJewel::EnItem_fn_800D00B0() {}
void EnElementJewel::EnItemThrowUp_fn_800D036C() {}
bool EnElementJewel::EnFiniteItem_fn_800D1318() { return true; }


bool EnCrown::EnFiniteItem_fn_800D1318() { return true; }
void EnCrown::EnItemThrowUp_fn_800D036C() {}
