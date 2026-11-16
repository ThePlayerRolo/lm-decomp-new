#include <JSystem/JUtility/JUTGamePad.hpp>
#include <dolphin/mtx.h>
#include <math.h>

#include "System/80009584.hpp"
#include "Unsorted/GamePad.hpp"


void fn_80009540(s32 param_1) {
    sGamePad->setButtonRepeat(JUTGamePad::MAINSTICK_LEFT | JUTGamePad::MAINSTICK_UP | JUTGamePad::MAINSTICK_RIGHT | JUTGamePad::MAINSTICK_DOWN |
        JUTGamePad::CSTICK_LEFT | JUTGamePad::CSTICK_UP | JUTGamePad::CSTICK_RIGHT | JUTGamePad::CSTICK_DOWN | 
        JUTGamePad::DPAD_LEFT | JUTGamePad::DPAD_UP | JUTGamePad::DPAD_RIGHT | JUTGamePad::DPAD_DOWN, 32 / param_1, 4 / param_1);
}

void fn_80009580() {}

f32 fn_80009584(Vec* param_1, Vec* param_2) {
    Vec diff;
    PSVECSubtract(param_1, param_2, &diff);
    return sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}
