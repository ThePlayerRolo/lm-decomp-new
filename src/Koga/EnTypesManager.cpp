#include <string.h>

#include "Koga/EnTypesManager.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/ParamInst.hpp"
#include "Koga/UnkUtil.hpp"
#include "Unsorted/ActorData.hpp"
#include "Unsorted/AssortedEnManager.hpp"
#include "macros.h"

dummy_float_data()
enemies_float_data()

// TODO figure this out and stick this in the appropriate class/place
// _0 is probably GroupID here
SomeIntStruct intStruct[4] = {{5, 72}, {32, 222}, {130, 11}, {318, 177}};
inline s32 forLine(u32 val) {
    for (s32 i = 0; i < 4; i++) {
        if (val <= intStruct[i]._0) {
            return i;
        }
    }

    return -1;
}


// https://decomp.me/scratch/6Feh6
EnemyParam::EnemyParam() : 
    PARAM_INIT(mLife, 0),
    PARAM_INIT(mHitDamage, 0),
    PARAM_INIT(mSpeed, 0),
    PARAM_INIT(mSpeedUnseen, 0),
    PARAM_INIT(mSpeedFight, 0),
    PARAM_INIT(mEyesight, 0),
    PARAM_INIT(mLightBindFrame, 0),
    PARAM_INIT(mMinLightBindRange, 0),
    PARAM_INIT(mMaxLightBindRange, 0),
    PARAM_INIT(mNumAtkKarakai, 0),
    PARAM_INIT(mNumAtkOrooro, 0),
    PARAM_INIT(mHikiPower, 0),
    PARAM_INIT(mEffectiveDeg, 0),
    PARAM_INIT(mTsuriHeight, 0),
    PARAM_INIT(mDisappearFrame, 0),
    PARAM_INIT(mAttackPattern1, 0),
    PARAM_INIT(mActAfterAttackSu, 0),
    PARAM_INIT(mActAfterAttackFa, 0),
    PARAM_INIT(mTsuriType, 0),
    PARAM_INIT(mElement, 0),
    PARAM_INIT(mCheckBox, 0),
    PARAM_INIT(mNormalItemTblId, 0),
    PARAM_INIT(mTsuriItemTblId, 0),
    PARAM_INIT(mPointerRange, 0),
    PARAM_INIT(mBrightColor, 0),
    PARAM_INIT(mAmbColor, 0) {
        // Maybe this isn't some default constructor based on mBrightColor / mAmbColor, since they both call fn_800D2FA0, which basically sets the defaults
        //  of these colors to -1 / 64, or maybe TBaseParam / TParamT needs its own inline base constructor?
    }

namespace Koga {
    EnTypesManager::EnTypesManager() {
        mEnParams = nullptr;
        mEnParams = new EnemyParam[0x17d];
    }

    EnTypesManager::~EnTypesManager() {
        delete [] mEnParams;
    }

    void EnTypesManager::newManager() {
        sManager = new EnTypesManager();
    }

    void EnTypesManager::deleteManager() {
        delete sManager;
        sManager = nullptr;
    }

    const char* EnTypesManager::fn_800DAAF8(s32 idx) {
       return ActorData::getActorName(idx);
    }

    s32 EnTypesManager::fn_800DABA4(ToolDataRef* param_1) {
        const char* name;
        
        if (param_1->isValid() && param_1->getToolData()->getValue(param_1->mEntryIndex, "name", &name)) {
            return EnTypesManager::fn_800DAB18(name);
        }

        return -1;
    }

    s32 EnTypesManager::fn_800DAB18(const char* pName) {
        u32 nameHash = hashStringSeperate(pName);

        for (u32 i = 0; i < 381; i++) {
            if (nameHash == hashStringSeperate(ActorData::getActorName(i))) {
                if (strcmp(pName, ActorData::getActorName(i)) == 0) {
                    return i;
                }
            }
        }

        return -1;
    }

    s32 EnTypesManager::fn_800DAC84(s32 idx) {
        u32 groupID = fn_80187920(ActorData::getGroupID(idx));
        return forLine(groupID);
    }

    s32 EnTypesManager::fn_800DAD00(s32 idx) {
        u32 groupID = fn_80187920(ActorData::getGroupID(idx));
        return intStruct[forLine(groupID)]._0;
    }

    s32 EnTypesManager::getEnemyLife(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mLife.get();
    }

    s32 EnTypesManager::getEnemyHitDamage(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mHitDamage.get();
    }

    s32 EnTypesManager::getEnemySpeed(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mSpeed.get();
    }


    s32 EnTypesManager::getEnemySpeedUnseen(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mSpeedUnseen.get();
    }


    s32 EnTypesManager::getEnemySpeedFight(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mSpeedFight.get();
    }

    s32 EnTypesManager::getEnemyEyesight(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mEyesight.get();
    }

    s32 EnTypesManager::getEnemyLightBindFrame(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mLightBindFrame.get();
    }

    f32 EnTypesManager::getEnemyMinLightBindRange(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mMinLightBindRange.get();
    }

    f32 EnTypesManager::getEnemyMaxLightBindRange(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mMaxLightBindRange.get();
    }

    f32 EnTypesManager::getEnemyPointerRange(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mPointerRange.get();
    }
    
    s32 EnTypesManager::getEnemyNumAtKarakai(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mNumAtkKarakai.get();
    }
    
    s32 EnTypesManager::getEnemyNumAtOrooro(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mNumAtkOrooro.get();
    }
    
    f32 EnTypesManager::getEnemyHikiPower(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mHikiPower.get();
    }
    
    f32 EnTypesManager::getEnemyEffectiveDeg(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mEffectiveDeg.get();
    }
    
    f32 EnTypesManager::getEnemyTsuriHeight(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mTsuriHeight.get();
    }

    s32 EnTypesManager::getEnemyActAfterAttackSu(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mActAfterAttackSu.get();
    }

    s32 EnTypesManager::getEnemyActAfterAttackFa(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mActAfterAttackFa.get();
    }

    s32 EnTypesManager::getEnemyNormalItemTblId(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mNormalItemTblId.get();
    }
    
    s32 EnTypesManager::getEnemyTsuriItemTblId(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mTsuriItemTblId.get();
    }
    
    s32 EnTypesManager::getEnemyDisappearFrame(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mDisappearFrame.get();
    }

    // https://decomp.me/scratch/rwCN5
    u32 EnTypesManager::getEnemyBrightColor(int enemyIdx) {
        return JUtility::TColor(getManager()->mEnParams[enemyIdx].mBrightColor.get());
    }
    
    // https://decomp.me/scratch/b6HLd
    u32 EnTypesManager::getEnemyAmbColor(int enemyIdx) {
        return JUtility::TColor(getManager()->mEnParams[enemyIdx].mAmbColor.get());
    }

    s32 EnTypesManager::getEnemyAttackPattern1(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mAttackPattern1.get();
    }
    
    s32 EnTypesManager::getEnemyTsuriType(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mTsuriType.get();
    }
    
    s32 EnTypesManager::getEnemyElement(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mElement.get();
    }
    
    bool EnTypesManager::getEnemyCheckBox(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mCheckBox.get() & 1;
    }

    s32 EnTypesManager::fn_800DB06C(s32 idx) {
        return intStruct[idx]._4;
    }
}
