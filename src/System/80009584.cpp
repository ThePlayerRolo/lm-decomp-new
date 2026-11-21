#include <JSystem/JUtility/JUTGamePad.hpp>
#include <math.h>

#include "System/80009584.hpp"
#include "Unsorted/GamePad.hpp"


void setDirectionalRepeat(s32 frameInterval) {
    sGamePad->setButtonRepeat(JUTGamePad::ANY_MAIN_STICK | JUTGamePad::ANY_CSTICK | JUTGamePad::PRESS_DPAD, 32 / frameInterval, 4 / frameInterval);
}

void fn_80009580() {}

f32 distance(Vec* from, Vec* to) {
    Vec diff;
    PSVECSubtract(from, to, &diff);
    return sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}
