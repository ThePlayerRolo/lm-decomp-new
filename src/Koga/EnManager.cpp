#include <JSystem/JKernel/JKRArchive.hpp>
#include <dolphin/mtx.h>
#include <string.h>

#include "Koga/EnManager.hpp"
#include "Koga/800E9568.hpp"
#include "Koga/EnTypesManager.hpp"
#include "Sato/EnThought.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Koga/ToolData.hpp"
#include "Koga/MissionMode.hpp"
#include "Unsorted/800627D8.hpp"
#include "Unsorted/AssortedEnManager.hpp"
#include "Koga/800E634C.hpp"
#include "Unsorted/Character.hpp"
#include "types.h"


namespace Koga {
    // https://decomp.me/scratch/fWEep
    EnManager::EnManager() : mInfoTable(nullptr) {
        _E44 = 0;
        _804.resetSize();
        mInfoTable = new ToolData();
    }

    // https://decomp.me/scratch/FXGcc
    EnManager::~EnManager() {
        delete mInfoTable;
    }

    void EnManager::loadCharacterInfo(JKRArchive* pArc) {
        mInfoTable->attach(reinterpret_cast<ToolData::JMapData*>(
            pArc->getResource('JMP ', "CharacterInfo")));
        EnManager::fn_800E52BC(mInfoTable);
    }

    // https://decomp.me/scratch/maIlk
    void EnManager::fn_800E46C0() {
        _E44 = 1;
        s32 maxPoint = getMaxAppearSlotIndex();

        for (int i = 0; i < maxPoint; i++) {
            _E08[i].fn_800E616C(&_E08[i].mPosition);
        }
        fn_80068EF8();

        unkEnManager1* currElm = &_4[0];
        for (int j = 0; j < maxPoint; currElm++, j++) {
            AppearPointSlot* appearPoint = &_E08[j];
            EnThought* temp4 = fn_800E5A14(nullptr);
            currElm->fn_800E9A0C(temp4);
            Character* someObj = currElm->fn_800E9C5C();
            appearPoint->_0 = someObj->_38; // also gets _38 from this?;
            EnThought* pThought = currElm->_0;
            pThought->setToolDataRef(appearPoint->_4, appearPoint->_8);
            currElm->fn_800E9CDC();
        }

        u32 i2;
        s32 temp4;
        unkEnManager1* currElm2;
        unkEnManager1* startElm;

        //startElm = _4 + maxPoint;
        for (i2 = 0; i2 < 4; i2++) {
            temp4 = EnTypesManager::fn_800DB06C(i2);
            currElm2 = startElm;
            for (int k = 0; k < fn_800E5E60(i2); k++, currElm2++, startElm++) {
                EnThought* temp5 = fn_800E5A14(temp4);
                currElm2->fn_800E9A0C(temp5);
                currElm2->fn_800E9ACC();
            }
        }
    }

    void EnManager::fn_800E52BC(ToolData* pCharacterInfo) {
        s32 appearPoint = sAppearPointSlotIndex + 1;
        u32 currAppearPoint = getLuigiAppearPoint();

        for (s32 i = 0; i < appearPoint; i++) {
            s32 entryIndex = findLuigiAppearIndex(pCharacterInfo, currAppearPoint);

            JGeometry::TVec3f zeroPos, pos;
            if (pCharacterInfo->getDataEntryNum() <= entryIndex) {
                JGeometry::TVec3f zeroPos;
                zeroPos.setAll(0.0f);
                _E08[i].init(&zeroPos, nullptr, -1);
            } else {
                pCharacterInfo->getValue(entryIndex, "pos_x", &pos.x);
                pCharacterInfo->getValue(entryIndex, "pos_y", &pos.y);
                pCharacterInfo->getValue(entryIndex, "pos_z", &pos.z);

                _E08[i].init(&pos, pCharacterInfo, entryIndex);
            }
        }
    }

    u32 EnManager::findLuigiAppearIndex(ToolData* pCharacterInfo, u32 expectedPoint) {
        u32 out;
        s32 luigiAppearPoint = 0;

        while (true) {
            int fieldIndex = pCharacterInfo->searchItemInfo("name");
            luigiAppearPoint = pCharacterInfo->findEntryByValue(fieldIndex, "luigi", luigiAppearPoint);
            if (luigiAppearPoint == -1) {
                return pCharacterInfo->getDataEntryNum();
            }

            out = 0;
            pCharacterInfo->getValue(luigiAppearPoint, "appear_point", &out);
            if (out == expectedPoint) { 
                return luigiAppearPoint;
            }
            
            luigiAppearPoint++;
        }
    }

    // https://decomp.me/scratch/9kvCn
    ToolDataRef* EnManager::fn_800E5488(s32 expectedIndex) {
        ToolDataRef* out;
        ToolData* pChar = mInfoTable;
        s32 idx = 0;

        while (true) {
            int fieldIndex = pChar->searchItemInfo("name");
            idx = pChar->findEntryByValue(fieldIndex, "luige", idx);
            if (idx == -1) {
                idx = pChar->getDataEntryNum();
                break;
            }

            u32 appearPoint = 0;
            pChar->getValue(idx, "appear_point", &appearPoint);
            if (appearPoint != expectedIndex) {
                break;
            }
            idx++;
        }

        ToolData* pCharFinal = mInfoTable;
        if (pCharFinal->getDataEntryNum() <= idx) {
            out->setToolData(nullptr);
            out->setEntryIndex(-1);
        } else {
            out->setToolData(pCharFinal);
            out->setEntryIndex(idx);
        }

        return out;
    }

    // https://decomp.me/scratch/Ztuvi
    Vec* EnManager::fn_800E5564(s32 param_1) {
        if (_E44 != 0) {
            // This probably pulls 0x0 from whatever object this is
            void* someObj = fn_800AD39C(param_1);
            //return someObj->_0; // At least, thats what it looks like?
        }

        return &_E08[param_1].mPosition;
    }

    // https://decomp.me/scratch/cBw99
    u32 Koga::EnManager::fn_800E55AC(s32 param_1) {
        if (_E44 != 0) {
            void* someObj = fn_800AD39C(param_1);
            //return someObj->_24; // This probably pulls 0x24 from whatever object this is
        }

        return _E08[param_1]._18;
    }

    s32 EnManager::fn_800E55F0(s32 appearSlotIndex) {
        return _E08[appearSlotIndex]._0;
    }

    // Based on ObjDiff, this seems to do some copy constructor stuff but the TVec3f struct seems to give me a lot of issues in this class
    // Also no-inline temproarily because it spills into the other function.
    s32 EnManager::fn_800E5660(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* out, f32 param_2) {
        JGeometry::TVec3f localOut;
        s32 result = fn_800E5784(pParam_1, &localOut);

        if (out != nullptr) {
            *out = localOut;
        }

        if (VECMag(localOut) < param_2) {
            return result;
        }

        return -1;
    }

    // https://decomp.me/scratch/AfFrv
    s32 EnManager::fn_800E5784(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* out) {
        int returnVal = -1;
        int maxAppear = getMaxAppearSlotIndex();
        f32 lowVal = MAX_FLOAT;

        if (maxAppear == 1 && out == nullptr) {
            return 0;
        }
        
        for (int i = 0; i < maxAppear; i++) {
            Vec* tVar;
            if (_E44 != 0) {
            // This probably pulls 0x0 from whatever object this is
            void* someObj = fn_800AD39C(i);
            //tVar = someObj->_0; // At least thats what it looks like
            } else {
                AppearPointSlot* tempVar = &_E08[i];
                tVar = &tempVar->mPosition;
            }

            JGeometry::TVec3f localOut;
            PSVECSubtract(tVar, pParam_1, &localOut);
            f32 localMag = VECMag(localOut);

            if (localMag < lowVal) {
                if (out != nullptr) {
                    *out = localOut;
                }
                lowVal = localMag;
                returnVal = i;
            }
        }

        return returnVal;
    }

    // https://decomp.me/scratch/shICK
    s32 EnManager::fn_800E5868(s32 param_1, s32 param_2) {
        unkEnManager1* temp = fn_800E58D4(param_1, nullptr, -1);
        if (temp == nullptr) {
            return -1;
        }

        if (param_2 >= 0) {
            temp->_0->fn_800C19CC(param_2);
        }

        Character* tempObj = temp->fn_800E9C5C();
        return tempObj->_38;
    }

    // https://decomp.me/scratch/cYSVu
    void EnManager::fn_800E59D4(s32 idx) {
        unkEnManager1* temp = &_4[idx];
        temp->fn_800E9ACC();
    }

    // TODO Fake Match
    void EnManager::fn_800E5A00(unkEnManager1Wrapper* pDest, EnManager* pMgr) {
        pDest->mBegin = pMgr->_4.begin();
        pDest->mEnd = pMgr->_4.end();
    }

    // https://decomp.me/scratch/fm1ig
    void EnManager::fn_800E5ABC(s32 idx) {
        unkEnManager1* temp = &_4[idx];
        temp->fn_800E9B44();
    }

    // https://decomp.me/scratch/3EURE
    void EnManager::fn_800E5E78(const char* pCreateName) {
        unkEnManager2* it = _804.getFirstMember();
        unkEnManager1* end = &_4[0x80];

        while (it != _804.getLastMember()) {
            if (strcmp(it->getCreateName(), pCreateName) != 0) {
                it++;
                continue;
            }

            // Some sort of missing struct missing here?
            s32 itEight = it->_8;
            s32 entryIndex = it->mCharacter.getEntryIndex();
            ToolData* charInfo = it->mCharacter.getToolData();
            s32 someVal = EnTypesManager::fn_800DAC84(itEight);
            unkEnManager1* p = &_4[0];

            // while (p != end && !matchesStatus(CHARSTATE_2, someVal)) {
            //     p++;
            // }

            unkEnManager1* found;
            if (p != end) {
                p->_0->setToolDataRef(charInfo, entryIndex);
                if (!found->fn_800E9A58(itEight)) {
                    found->fn_800E9ACC();
                    found = nullptr;
                } else {
                    found = p;
                }
            } else {
                found = nullptr;
            }

            if (found != nullptr) {
                it = _804.eraseMember(it);
            }
        }
    }
}

unkEnManager2::unkEnManager2() {
    _8 = -1;
}

// https://decomp.me/scratch/IqD70
unkEnManager2::unkEnManager2(const ToolDataRef& rDest) {
    mCharacter = ToolDataRef(rDest.mToolData, rDest.mEntryIndex);
    _8 = Koga::EnTypesManager::fn_800DABA4(&mCharacter);
}

// https://decomp.me/scratch/6sXfk
u32 unkEnManager2::fn_800E601C() {
    JGeometry::TVec3f pos;

    mCharacter.mToolData->getValue(mCharacter.mEntryIndex, "pos_x", &pos.x);
    mCharacter.mToolData->getValue(mCharacter.mEntryIndex, "pos_y", &pos.y);
    mCharacter.mToolData->getValue(mCharacter.mEntryIndex, "pos_z", &pos.z);

    return fn_80017ADC(pos, -1);
}

// https://decomp.me/scratch/cfVnh
const char* unkEnManager2::getCreateName() {
    const char* create_name = nullptr;
    
    if (fn_800E6134().isValid()) {
        ToolDataRef vRef = fn_800E6134();
        vRef.mToolData->getValue(vRef.mEntryIndex, "create_name", &create_name);
    }

    return create_name;
}

// https://decomp.me/scratch/bq3Q2
ToolDataRef unkEnManager2::fn_800E6134() {
    return ToolDataRef(mCharacter.mToolData, mCharacter.mEntryIndex);
}

void AppearPointSlot::init(Vec* pPos, Koga::ToolData* pCharInfo, int entryIndex) {
    _4 = pCharInfo;
    _8 = entryIndex;
    mPosition = *pPos;
}

void AppearPointSlot::fn_800E616C(Vec* pParam_1) {
    _18 = fn_80017ADC(*pParam_1, -1);
}

unkEnManager1::unkEnManager1() {
    _0 = 0;
    mState = DEFAULT_CHARSTATE;
    _8 = 0;
}
