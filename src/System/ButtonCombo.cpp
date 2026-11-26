#include <JSystem/JUtility/JUTGamePad.hpp>

#include "System/Scenes/SceneManager.hpp"
#include "Unsorted/GamePad.hpp"
#include "System/ButtonCombo.hpp"

#include "macros.h"

dummy_float_data()
static u32 sComboLRLR[5] = {JUTGamePad::L, JUTGamePad::R, JUTGamePad::L, JUTGamePad::R, 0};
static u32 sCombopUpUpDownDownDpad[5] = {JUTGamePad::DPAD_UP, JUTGamePad::DPAD_UP, 
    JUTGamePad::DPAD_DOWN, JUTGamePad::DPAD_DOWN, 0};
static u32 sCombopLeftLeftRightRightDpad[5] = {JUTGamePad::DPAD_LEFT, JUTGamePad::DPAD_LEFT, 
    JUTGamePad::DPAD_RIGHT, JUTGamePad::DPAD_RIGHT, 0};

ButtonCombo sUnkButtonCombos[3] = {sComboLRLR, sCombopUpUpDownDownDpad, sCombopLeftLeftRightRightDpad};

ButtonCombo::ButtonCombo(u32* pSequence) {
    mIndex = 0;
    mIsActive = 0;
    mButtonSequence = pSequence;
    mLastTick = 0;
    _8 = 0;
}

s32 ButtonCombo::update() {
    if (mLastTick == SceneManager::sTotalFrameCount) {
        return mIsActive;
    }

    mLastTick = SceneManager::sTotalFrameCount;

    u32 triggerVal = sGamePad->testTrigger(JUTGamePad::ANY_INPUT);
    if (triggerVal == 0) {
        return mIsActive;
    }
    
    if (triggerVal == mButtonSequence[mIndex]) {
        mIndex++;
    } else {
        mIndex = 0;
    }

    if (mButtonSequence[mIndex] == 0) {
        mIndex = 0;
        mIsActive ^= 1;
    }

    return mIsActive;
}
