#include "Koga/CharacterColManager.hpp"
#include "Unsorted/ActorData.hpp"

static const unkCharactColStruct2 sUnkCharactColStruct = {
    {-1, 50.0, 0.0, 50.0, 0.0},
    {4.0, 100.0, 0.0, -50.0,0.0},
    {100.0, 100.0, 100.0, 0.0, 0.0, 0.0}
};

// Fake Match for now, will need to not const_cast, probably
CharacterColElement::CharacterColElement() : mGroupID(0), _18(1) {
    _1C.addMember(const_cast<unkCharactColStruct1*>(&sUnkCharactColStruct._0));
    _0._4 = _1C.getArray();
    _0._0 = _1C.getSize();
    _0._8 = 1;
    _0._C = &_C0;
    _0._10 = &_D4;
    _C0 = sUnkCharactColStruct._14;
    _D4 = sUnkCharactColStruct._28;
}

void CharacterColElement::init(s32 param_1) {
    _1C.resetSize();
    mGroupID = ActorData::getGroupID(param_1);

    unkCharactColStruct5* unk = unkCharactColStruct5::lbl_8038E118[param_1] != nullptr ? 
        unkCharactColStruct5::lbl_8038E118[param_1] : unkCharactColStruct5::lbl_8038DD00[ActorData::getGroupID(param_1)];

    _18 = 0;
    for (int i = 0; i < unk->_0; i++) {
        unkCharactColStruct1* unk2 = &unk->_4[i];
        _1C.addMember(unk2);
    }

    _0._4 = _1C.getArray();
    _0._0 = _1C.getSize();
    _0._8 = unk->_8;
    _0._C = &_C0;
    _0._10 = &_D4;

    if (unk->_C != nullptr) {
        _C0 = *unk->_C;
    }

    if (unk->_10 != nullptr) {
        _D4 = *unk->_10;
    }
}

CharacterColManager::CharacterColManager() {
    _4 = nullptr;
    _4 = new CharacterColElement[381];

    for (CharacterColElement* currElm = begin(); currElm != end(); currElm++) {
        currElm->init(currElm - begin()); // Some sort of index management here, idk its gross
    }
}

CharacterColElement::~CharacterColElement() {}

CharacterColManager::~CharacterColManager() {
    delete [] _4;
}
