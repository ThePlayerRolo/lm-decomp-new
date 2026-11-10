#include "Koga/800E9568.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/EnTypesManager.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Koga/ToolData.hpp"
#include "Sato/EnThought.hpp"
#include "Unsorted/ActorData.hpp"
#include "dolphin/macros.h"
#include "types.h"
#include "Koga/800E82D8.hpp"

// Does not match due to some ToolData inline shenanigans. Seems to match more as a u32 input though than u8
// https://decomp.me/scratch/PdZKG
void fn_800E82D8(ToolDataRef* param_1, u32 param_2) {
    FORCE_DONT_INLINE
    if (param_2 == -1) {
        param_1->reset();
        return;
    }

    Koga::ToolData* treasureTable = Koga::GameModeUtil::getJmpResource("treasuretable");
    if (treasureTable == nullptr) {
        param_1->reset();
        return;
    }

    s32 roomNo = treasureTable->findEntryByValue(treasureTable->searchItemInfo("room"), static_cast<u8>(param_2), 0);
    if (roomNo == -1) {
        param_1->reset();
        return;
    }

    param_1->setToolData(treasureTable);
    param_1->setEntryIndex(roomNo);
}

void fn_800E83A0(EnThought* param_1) {
    s32 temp;
    s32 enNormalTblId = fn_800E8438(param_1);

    // _900 has something else we need to check against, cannot continue without more details
    if (param_1->_900 && enNormalTblId == 3) {
        ToolDataRef sheart = fn_800E8D1C("sheart");
        temp = fn_800E8EF4(&sheart, param_1->getCharacter()->_44, nullptr);
    } else {
        ToolDataRef tRef = fn_800E84CC(enNormalTblId);
        temp = fn_800E8EF4(&tRef, param_1->getCharacter()->_44, nullptr);
    }
}

// There is probably some inline or macro as this pattern comes up a few times in several other files.
s32 fn_800E8438(EnThought* param_1) {
    ToolDataRef tRef = param_1->getToolDataRef();
    Koga::ToolData* pData = tRef.mToolData;
    u32 itemNum = 0;
    s32 idx = tRef.mEntryIndex;

    if (ToolDataRef::isValid(pData, idx) && pData->getValue(idx, "item_table", &itemNum) && itemNum != 0) {
        return itemNum;
    }

    return Koga::EnTypesManager::getEnemyNormalItemTblId(param_1->getCharacter()->_3C);
}


// https://decomp.me/scratch/iXsZ8
ToolDataRef fn_800E84CC(s32 param_1) {
    ToolDataRef vRef;
    Koga::ToolData* itemAppear = Koga::GameModeUtil::getJmpResource("itemappeartable");
    
    if (itemAppear == nullptr) {
        vRef.reset();
        return ToolDataRef(&vRef);
    }

    int entryIdx = fn_800E85C8(param_1);
    if (entryIdx > itemAppear->getDataEntryNum()) {
        vRef.reset();
        return ToolDataRef(&vRef);
    }

    // Calls upon fn_80009638() to get some value, which is probably the below fieldIdx
    int fieldIdx = 0;
    fn_800E8D1C(itemAppear->getStringValue(entryIdx, fieldIdx));
    return vRef;
}

// https://decomp.me/scratch/mcYqn
ToolDataRef fn_800E8658(s32 param_1, s32 param_2, s32 param_3) {
    ToolDataRef tmp;
    Koga::ToolData* itemFishing = Koga::GameModeUtil::getJmpResource("itemfishingtable");

    if (itemFishing == nullptr) {
        tmp.reset();
        return ToolDataRef(&tmp);
    }

    if (param_1 <= itemFishing->getDataEntryNum()) {
        tmp.reset();
        return ToolDataRef(&tmp);
    }

    int fieldCount = itemFishing->getJMapData()->mNumFields;
    if (param_3 <= fieldCount) {
        if (param_3 <= param_2) {
            param_2 = (param_2 - param_3) - (
                ((param_2 - param_3) / (fieldCount - param_3) * (fieldCount - param_3))) + param_3;
        }
    } 
    
    else if (fieldCount <= param_2) {
        param_3 = fieldCount - 1;
    }

    const char* itemName = itemFishing->getStringValue(param_2, param_3);
    if (strcmp(itemName, "-") == 0) {
        tmp.reset();
        return ToolDataRef(&tmp); 
    }

    return fn_800E8D1C(itemName);;
}

void fn_800E87B0(u8* param_1, s32 param_2) {
    u32 temp2;
    Koga::ToolData* itemInfo = Koga::GameModeUtil::getJmpResource("itemappeartable");
    if (itemInfo == nullptr) {
        return;
    }

    s32 numFields = itemInfo->getJMapData()->mNumFields;
    for (s32 i = 0; i < numFields; i++) {
        ToolDataRef tRef = fn_800E8D1C(itemInfo->getStringValue(param_2, i));
        if (!fn_800E91B8(&tRef) && !fn_800E9224(&tRef)) {
            s32 temp = fn_800E8E78(&tRef);
            if (temp < 0) {
                continue;
            }

            *param_1 = ActorData::getGroupID(temp);
        }
    }
}

void fn_800E8880(u32 param_1) {
    u8 temp2;
    ToolDataRef tRef;
    
    fn_800E82D8(&tRef, param_1);

    if (!tRef.isValid()) {
        return;
    }

    const char* other;
    tRef.getToolData()->getValue(tRef.getEntryIndex(), "other", &other);
    ToolDataRef temp = fn_800E8D1C(other);
    fn_800E8E0C(&temp, &temp2);
}

ToolDataRef::ToolDataRef(const ToolDataRef* pSrc) {
    setToolData(pSrc->mToolData);
    setEntryIndex(pSrc->mEntryIndex);
}

// https://decomp.me/scratch/qYZ9J
ToolDataRef* fn_800E8D1C(ToolDataRef* temp, const char* pName) {
    Koga::ToolData* itemInfo = Koga::GameModeUtil::getJmpResource("iteminfotable");
    int fieldIndex = itemInfo->searchItemInfo("name");
    int charFound = itemInfo->findEntryByValue(fieldIndex, pName, 0);

    if (charFound == -1) {
        itemInfo = nullptr;
        charFound = -1;
    } 
    
    temp->setToolData(itemInfo);
    temp->setEntryIndex(charFound);

    return temp;
}

// Needed to match isNameValid/Money for now, otherwise it inlines this function.
// https://decomp.me/scratch/JdML7
const char* fn_800E8DAC(ToolDataRef* pRef) {
    FORCE_DONT_INLINE;
    return pRef->getStringValue("name");
}

void fn_800E8E0C(ToolDataRef* pRef, bool* param_2) {
    if (fn_800E91B8(pRef)) {
        return;
    }

    if (fn_800E9224(pRef)) {
        return;
    }

    s32 temp = fn_800E8E78(pRef);
    if (temp < 0) {
        return;
    }

    param_2[ActorData::getGroupID(temp)] = 1;
}

s32 fn_800E8E78(ToolDataRef* param_1) {
    const char* char_name = param_1->getStringValue("character_name");
    if (char_name == nullptr) {
        return -1;
    }

    return Koga::EnTypesManager::fn_800DAB18(char_name);
}

// Matches except one instruction. Also depends on the getName above to not inline.
// https://decomp.me/scratch/wZ68w
bool fn_800E91B8(ToolDataRef* pRef) {
    bool nameValid = true;

    if (pRef->isValid() && strcmp(fn_800E8DAC(pRef), "nothing") != 0) {
        nameValid = false;
    }

    return nameValid;
}

// Matches except one instruction. Also depends on the getName above to not inline.
// https://decomp.me/scratch/WT1gF
bool fn_800E9224(ToolDataRef* pRef) {
    bool nameMoney = false;

    if (pRef->isValid()) {
        if (strcmp(fn_800E8DAC(pRef), "money") == 0) {
            nameMoney = true;
        }
    }

    return nameMoney;
}
