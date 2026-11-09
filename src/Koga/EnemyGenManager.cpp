#include <string.h>
#include <dolphin/macros.h>

#include "Koga/EnemyGenManager.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Koga/MissionMode.hpp"
#include "JSystem/JGeometry/JGVec3.hpp"
#include "Koga/ToolData.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "Sato/EnZako.hpp"
#include "macros.h"

dummy_float_data()

EnemyGenerator::EnemyGenerator() {
    fn_800C2500();
}

void EnemyGenerator::fn_800C2500() {
   _808 = nullptr;
   _80C = 0;
   _810 = 0;
   mGenPath.reset(); 
   _820.resetSize();
   _870 = 0;
   destroyStrategy();
   fn_800C2560();
}

void EnemyGenerator::fn_800C2560() {
    _860 = 0;
}

EnemyGenerator::~EnemyGenerator() {}

// https://decomp.me/scratch/GhkkW
EnZako* EnemyGenerator::fn_800C25F0(s32 param_1, s32 param_2) {
    if (fn_800C2830("max_enemy") != nullptr && fn_800C2830("max_enemy") <= _860) {
        return nullptr;
    }

    s32 temp2 = _820.getSize();
    if (fn_800C2830("max_enemy_once") <= temp2) {
        return nullptr;
    }

    if (!(_870 & 0x2)) {
        JGeometry::TVec3f pos = mPos;
        // Does something with with mPos
    }

    if (!(_870 & 0x1)) {
        if (!fn_800E7174(&mPos, -1)) {
            return nullptr;
        }
    }

    if (_820.getSize() >= 0xF) {
        return nullptr;
    }

    if (Koga::EnManager::fn_800E4A04(param_1)) {
        return nullptr;
    }

    s32 sVal = _810->fn_800E5868(param_1, param_2);
    if (sVal < 0) {
        return nullptr;
    }

    EnThought* enChar = _810->fn_800E5A80(sVal);
    EnZako* eZako = dynamic_cast<EnZako*>(enChar);
    eZako->set810(this);
    _820.addMember(&eZako);
    _860++;
    return eZako;
}

ToolDataRef EnemyGenerator::fn_800C2784() {
    ToolDataRef ref;
    ref.init(_808, _80C);
    return ref;
}

Koga::ToolData* EnemyGenerator::fn_800C2798() {
    if (!mGenPath.getJMapData()) {
        ToolDataRef ref;
        ref.setToolData(_808);
        ref.setEntryIndex(_80C);
        const char* pathName = nullptr;
        bool isValid = ref.getToolData() != nullptr && ref.getEntryIndex() >= 0;

        if (isValid && ref.getToolData()->getValue(ref.getEntryIndex(), "path_name", &pathName) && pathName != nullptr) {
            mGenPath.attach(reinterpret_cast<Koga::ToolData::JMapData*>(Koga::GameModeUtil::getPathResource(pathName)));   
        }
    }

    return &mGenPath;
}

// https://decomp.me/scratch/QFptY
s32 EnemyGenerator::fn_800C2830(const char* pKeyName) {
    u32 out = 0;
    ToolDataRef ref;
    ref.setToolData(_808);
    ref.setEntryIndex(_80C);
    ref.getToolData()->getValue(ref.getEntryIndex(), pKeyName, &out);
    return out;
}

namespace Koga {

    EnemyGenManager::EnemyGenManager()  {
        _8 = true;
        mEnemyGens = new EnemyGenerator[MAX_ENEMY_GENS];
    }

    EnemyGenManager::~EnemyGenManager() {
        delete [] mEnemyGens;
    }

    // https://decomp.me/scratch/w96BL
    BOOL EnemyGenManager::vt_0C(ToolDataRef* pRef) {
        const char* entryName;
        const char* genType;
        ToolDataRef localRef = *pRef;
        
        if (!localRef.getToolData()->getValue(localRef.getEntryIndex(), "name", &entryName)) {
            return false;
        }

        if (strcmp(entryName, "generator") != 0) {
            return false;
        }

        EnemyGenerator* freeGen = findFreeEnemyGen();

        if (freeGen != end()) {
            // I think there is some other Loop here but can't get it right for the minute. Leaving this at like ~70% until these other functions are done.
            // for (ToolDataRef** pIter = curr->_820.getFirstMember(); pIter != curr->_820.getMaxMember(); curr++) {}
            genType = "";
            localRef.getToolData()->getValue(localRef.getEntryIndex(), "type", &genType);
            //int uVar1 = fn_800DAB18(genType);
            //void* pcVar3 = fn_800DAC54();
            freeGen->_808 = localRef.getToolData();
            freeGen->_80C = localRef.getEntryIndex();
            freeGen->_814 = 0; //uVar1
            freeGen->_810 = MissionMode::sMissionMode->getEnManager();
            // some call on pcVar3 / localRef?

            freeGen->destroyStrategy();
            freeGen->setStrategy(0); // maybe uses pcVar3 here
            // fn_800C1BAC(curr) call?

            Koga::ToolData* tData = freeGen->_808;
            s32 currIdx = freeGen->_80C;
            tData->getValue(currIdx, "pos_x", &freeGen->mPos.x);
            tData->getValue(currIdx, "pos_y", &freeGen->mPos.y);
            tData->getValue(currIdx, "pos_z", &freeGen->mPos.z);

            freeGen->getStrategy()->init();   
        }
        
        return true;
    }

    // https://decomp.me/scratch/2kU0Q
    BOOL EnemyGenManager::vt_10(ToolDataRef* pRef) {
        // This does some pass by value maybe or copy constructor? dunno, something like that
        Koga::ToolData* pData = pRef->getToolData();
        s32 entryIdx = pRef->getEntryIndex();
        const char* isGenerator;

        if (!pData->getValue(entryIdx, "name", &isGenerator)) {
            return false;
        }
        
        if (strcmp(isGenerator, "generator") != 0) {
            return false;
        }

        EnemyGenerator* enGen = searchEnemyGen(pData, entryIdx);
        if (enGen == end()) {
            return false;
        }

        for (EnZako** pIter = enGen->_820.getArray(); pIter != enGen->_820.getLastMember(); enGen++) {
            //some call out to fn_800C0EBC?
        }

        enGen->fn_800C2500();
        return true;
    }

    // https://decomp.me/scratch/Js1a9
    BOOL EnemyGenManager::vt_14(ToolDataRef* pRef, char* message) {
        // This does some pass by value maybe or copy constructor? dunno, something like that
        Koga::ToolData* pData = pRef->getToolData();
        s32 entryIdx = pRef->getEntryIndex();
        const char* isGenerator;
        
        if (!pData->getValue(entryIdx, "name", &isGenerator)) {
            return false;
        }
        
        if (strcmp(isGenerator, "generator") != 0) {
            return false;
        }

        EnemyGenerator* enGen = searchEnemyGen(pData, entryIdx);
        if (enGen == end()) {
            return false;
        }

        if (strcmp(message, "start") == 0) {
            enGen->getStrategy()->setNextState(0x104);
        } else if (strcmp(message, "stop") == 0) {
            enGen->getStrategy()->setNextState(0x103);
        } else {
            return false;
        }

        return true;
    }

    void EnemyGenManager::fn_800C2F44() {
        if (_8 == 0) {
            return;
        }
        
        for (EnemyGenerator* curr = begin(); curr != end(); curr++) {
            if (curr->getStrategy() != nullptr) {
                curr->updateStrategy();
            }
        }
    }
}

EnemyStrategy* EnemyGenerator::getGenStrategy() {
    return getStrategy();
}
