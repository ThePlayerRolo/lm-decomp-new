#include <JSystem/JUtility/JUTGamePad.hpp>
#include <math.h>

#include "System/80009584.hpp"
#include "Unsorted/GamePad.hpp"


void setDirectionalRepeat(s32 frameInterval) {
    sGamePad->setButtonRepeat(JUTGamePad::MAINSTICK_LEFT | JUTGamePad::MAINSTICK_UP | JUTGamePad::MAINSTICK_RIGHT | JUTGamePad::MAINSTICK_DOWN |
        JUTGamePad::CSTICK_LEFT | JUTGamePad::CSTICK_UP | JUTGamePad::CSTICK_RIGHT | JUTGamePad::CSTICK_DOWN | 
        JUTGamePad::DPAD_LEFT | JUTGamePad::DPAD_UP | JUTGamePad::DPAD_RIGHT | JUTGamePad::DPAD_DOWN, 32 / frameInterval, 4 / frameInterval);
}

void fn_80009580() {}

f32 distance(Vec* from, Vec* to) {
    Vec diff;
    PSVECSubtract(from, to, &diff);
    return sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}
