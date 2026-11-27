#include "Sato/EnItems.hpp"
#include "JSystem/JKernel/JKRMemArchive.hpp"
#include "Koga/CharacterEventObserver.hpp"
#include "Koga/EnAttackBase.hpp"
#include "Sato/EnZako.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "Unsorted/PlayerInteraction.hpp"
#include "System/MathUtils.hpp"

dummy_float_data()
enemies_float_data()

// Some Particle/Effect spawning function
void fn_80164F5C(u32, const JGeometry::TVec3f&, const JGeometry::TVec3f&);
JKRMemArchive* fn_80066FB4();

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

EnKeyParams EnKey::sParams;

EnItem::EnItem() : mAlwaysTrueCond(), mCondStrategies(), mAppearAlphaCond(), _90(false), _91(0), _94(1), _98(nullptr, 0) {}
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
    if ((_94 & 0x1) != 0) {
        fn_80164F5C(70, getZako()->getCharacter()->getPosition(), CONVERT_VEC_REF(gZeroVec));
    }

    return true;
}

bool EnItem::onPlayerLeftRoom(Koga::CharacterEvent* msg) {
    static const Koga::CharacterEvent::Message lbl_804D33C8 = Koga::CharacterEvent::MESSAGE_CAPTURE_END;

    if ((_94 & 0x10) == 0) { return false; }

    _94 &= ~0x1;

    getZako()->fn_800C0F08(Koga::CharacterEvent(lbl_804D33C8));

    return true;
}

bool EnItem::state_0_Init() {
    initItemParams();
    return true;
}

bool EnItem::state_0_Behavior() {
    if ((_94 & 0x4) != 0) {
        setNextState(3);
        return true;
    }

    const ToolDataRef& dataRef = getZako()->getToolDataRef();
    Koga::ToolData* pData = dataRef.mToolData;
    s32 entryIdx = dataRef.mEntryIndex;

    u32 cond_type = 2;
    u32 appear_type = 3;

    if (dataRef.isValid()) {
        pData->getValue(entryIdx, "cond_type", &cond_type);
        pData->getValue(entryIdx, "appear_type", &appear_type);
    }

    _88 = getCondStrategy(cond_type);
    _8C = getAppearStrategy(appear_type);

    setNextState(1);

    return true;
}

bool EnItem::state_1_Init() {
    _88->setNextState(0);
    return true;
}

bool EnItem::state_1_Behavior() {
    _88->update();

    if (_88->getCurrentState() == 256) {
        setNextState(2);
        return true;
    }

    getZako()->getCharacter()->setVelocity(CONVERT_VEC_REF(gZeroVec));
    return true;
}

bool EnItem::state_2_Init() {
    _8C->setNextState(0);
    return true;
}

bool EnItem::state_2_Behavior() {
    _8C->update();

    if (_8C->getCurrentState() == 256) {
        setNextState(3);
    }

    return true;
}

bool EnItem::state_3_Init() {
    EnItem_fn_800D00A8();
    return true;
}

bool EnItem::state_3_Behavior() {
    if (_90) {
        getZako()->getCharacter()->setVelocity(CONVERT_VEC_REF(gZeroVec));
        return true;
    }

    EnItem_fn_800D00AC();
    if (fn_800CFFDC()) {
        fn_800D00BC();
    }

    return true;
}


void EnItem::initItemParams() { }

bool EnItem::fn_800CFFDC() {
    if (!fn_800D0070()) {
        return false;
    }

    Character* character = getZako()->getCharacter();
    // TODO: Relies on external functions and structs not decompiled yet.
}

bool EnItem::fn_800D0070() {
    if (getZako()->getCharacter()->mAlpha1 != 255) {
        return false;
    }

    if (getTimer() < 30) {
        return false;
    }

    return true;
}

void EnItem::EnItem_fn_800D00A8() {}

void EnItem::EnItem_fn_800D00AC() {}

void EnItem::EnItem_fn_800D00B0() {}

bool EnItem::EnItem_fn_800D00B4() { return false; }

// TODO: Relies on external functions and structs not decompiled yet.
// void EnItem::fn_800D00BC() { }

// TODO: Relies on external functions and structs not decompiled yet.
// void EnItem::fn_800D01EC() { }

EnemyStrategy* EnItem::getCondStrategy(s32 condType) {
    EnemyStrategy* condStrategy = mCondStrategies.setCurrentStategy(condType);

    if (condStrategy != nullptr) {
        condStrategy->mpZako = mpZako;
        condStrategy->mpUserData = mpUserData;
    }
    return condStrategy;
}

EnemyStrategy* EnItem::getAppearStrategy(s32 appearType) {
    EnemyStrategy* appearStrategy;

    if (appearType != 4) {
        appearStrategy = &mAlwaysTrueCond;
    } else {
        appearStrategy = &mAppearAlphaCond;
    }

    if (appearStrategy != nullptr) {
        appearStrategy->mpZako = mpZako;
        appearStrategy->mpUserData = mpUserData;
    }

    return appearStrategy;
}

///////////////////////////////

void EnItemThrowUp::EnItem_fn_800D00A8() {
    mThrowUp.mpZako = mpZako;
    mThrowUp.mpUserData = mpUserData;
    mThrowUp.setNextState(0);
    mThrowCount = 0;
}

void EnItemThrowUp::EnItem_fn_800D00AC() {
    mThrowUp.update();

    if (mThrowUp.getCurrentState() == 2) {
        onThrowUp();
        mThrowCount++;
    }
}

void EnItemThrowUp::onThrowUp() { }
///////////////////////////////

EnKey::EnKey() : _210(false) {
    sParams.mParams.load(sParams.mParams.mPrmPath,fn_80066FB4());
}

EnFiniteItem::~EnFiniteItem() {}

bool EnKey::onCaptureEnd(Koga::CharacterEvent* msg) {
    EnItem::onCaptureEnd(msg);

    if (!_210) { return false; }

    u32 openDoorNo;

    if (ToolDataRef::getValue(&getZako()->getToolDataRef(), "OpenDoorNo", &openDoorNo)) {
            PlayerInteractionInfo info;
            info._88 = openDoorNo;
            sendPlayerInteraction(0, INTERACTION_KEY_GET, &info);
    } else {
        ToolDataRef dataRef2 = _98;

        if (ToolDataRef(_98).isValid()) {
            u32 openDoorNo;
            if (dataRef2.getToolData()->getValue(dataRef2.getEntryIndex(), "OpenDoorNo", &openDoorNo)) {
                PlayerInteractionInfo info;
                info._88 = openDoorNo;
                sendPlayerInteraction(0, INTERACTION_KEY_GET, &info);
            }
        }
    }

    return true;
}

void EnKey::initItemParams() {
    mThrowUp.loadParamsFromFile("/param/th/EnThrowupKey.prm");
    _94 |= 2;

    if (!getZako()->getToolDataRef().isValid()) {
        _94 |= 0x14;
    }

    const char* createName = "";

    const char* createNameCheck = "3_1";


    if (ToolDataRef::getValue(&getZako()->getToolDataRef(), "create_name", &createName)) {
        char** i = &createNameCheck;

        while (*i != "" && strcmp(*i, createName) != 0) {
            i++;
        }

        if (*i != "") {
            fn_8018A2A0(0x381C);
        }
    }
}

void EnKey::EnItem_fn_800D00A8() {}
void EnKey::EnItem_fn_800D00AC() {}
void EnKey::onThrowUp() {}
void EnKey::EnItem_fn_800D00B0() {}
bool EnKey::EnFiniteItem_fn_800D1318() { return true; }

void EnMarioItem::initItemParams() {}
void EnMarioItem::EnItem_fn_800D00A8() {}
void EnMarioItem::EnItem_fn_800D00AC() {}
void EnMarioItem::onThrowUp() {}
void EnMarioItem::EnItem_fn_800D00B0() {}
bool EnMarioItem::EnFiniteItem_fn_800D1318() { return true; }

///////////////////////////////

void EnNegativeItem::initItemParams() {}
void EnNegativeItem::EnItem_fn_800D00A8() {}
void EnNegativeItem::EnItem_fn_800D00AC() {}
void EnNegativeItem::onThrowUp() {}
void EnNegativeItem::EnItem_fn_800D00B0() {}


EnFiniteItem::EnFiniteItem() : _1B0(0),
    mParams("/param/th/EnFiniteItem.prm"),
    PARAM_INIT(mIgnoreTime, 90),
    PARAM_INIT(mLife, 480),
    PARAM_INIT(mBlinkFeq, 3),
    PARAM_INIT(mBlinkLife, 50)
{
    set_0C(false);
}


void EnFiniteItem::vt_08() {
    fn_800D00BC();
}

void EnFiniteItem::EnFiniteItem_fn_800D12E8() {
    getZako()->getCharacter()->setVisible();
}

void EnFiniteItem::EnFiniteItem_fn_800D1300() {
    getZako()->getCharacter()->setInvisible();
}

bool EnFiniteItem::EnFiniteItem_fn_800D1318() { return false; }

///////////////////////////////

void EnHeartItem::init() {}
EnHeartItem::~EnHeartItem() {}
void EnHeartItem::initItemParams() {}
void EnHeartItem::EnItem_fn_800D00A8() {}
void EnHeartItem::EnItem_fn_800D00AC() {}
void EnHeartItem::onThrowUp() {}
void EnHeartItem::EnItem_fn_800D00B0() {}


///////////////////////////////

EnJewel::~EnJewel() {}
void EnJewel::initItemParams() {}
void EnJewel::EnItem_fn_800D00B0() {}
void EnJewel::EnItem_fn_800D00A8() {}
void EnJewel::EnItem_fn_800D00AC() {}
void EnJewel::onThrowUp() {}

///////////////////////////////

EnPearl::EnPearl() {}
void EnPearl::initItemParams() {}
bool EnPearl::EnItem_fn_800D00B4() { return true; }


void EnGold::initItemParams() {}
void EnGold::onThrowUp() {}


EnElementJewel::EnElementJewel() {}
EnElementJewel::~EnElementJewel() {}
bool EnElementJewel::onCaptureEnd(Koga::CharacterEvent* msg) { return true; }
void EnElementJewel::initItemParams() {}
void EnElementJewel::EnItem_fn_800D00B0() {}
void EnElementJewel::onThrowUp() {}
bool EnElementJewel::EnFiniteItem_fn_800D1318() { return true; }


bool EnCrown::EnFiniteItem_fn_800D1318() { return true; }
void EnCrown::onThrowUp() {}
