#include <dolphin/os/OSFastCast.h>
#include <JSystem/JUtility/JUTGamePad.hpp>
#include <dolphin/pad.h>

#include "System/80005C00.hpp"
#include "System/800080DC.hpp"
#include "System/DisplayUtil.hpp"
#include "Unsorted/GamePad.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "System/Scenes/SceneManager.hpp"
#include "dolphin/os/OSResetSW.h"

s32 lbl_804D7FF0;
u8 lbl_80396900[0x4000];
UnkThread lbl_8039A900;

static void* fn_80005C30(void*);
static void fn_80005C8C(UnkThread*);
static s32 fn_80005CF8();

void fn_80005C00() {
    lbl_804D7FF0 = 0;
    fn_80005C8C(&lbl_8039A900);
}

void* fn_80005C30(void*) {
    OSInitFastCast();
    while (true) {
        OSReceiveMessage(&lbl_8039A900.mMsgQueue, nullptr, OS_MESSAGE_BLOCK);
    }
}

void fn_80005C8C(UnkThread* pThread) {
    OSInitMessageQueue(&pThread->mMsgQueue, &pThread->mMsg, 1);
    u32 size = sizeof(lbl_80396900);
    OSCreateThread(&pThread->mThread, fn_80005C30, nullptr, &lbl_80396900[size], size, 1, 1);
    OSResumeThread(&pThread->mThread);
}

s32 fn_80005CF8() {
    static s32 lbl_804D7FF4 = 0;
    static s32 lbl_804D7FFC = 0;

    if (!sGamePad->testButton(JUTGamePad::START)) {
        lbl_804D7FF4 = 0;
        lbl_804D7FFC = 0;
        return false;
    }
    
    if (!sGamePad->testButton(JUTGamePad::B)) {
        lbl_804D7FF4 = 0;
        lbl_804D7FFC = 0;
        return false;
    }
    
    if (!sGamePad->testButton(JUTGamePad::X)) {
        lbl_804D7FF4 = 0;
        lbl_804D7FFC = 0;
        return false;
    }
    
    if (lbl_804D7FFC != 0) {
        return false;
    }

    lbl_804D7FF4 += 1;

    if (lbl_804D7FF4 < 30 / getFrameRateDivisor()) {
        return false;
    }
    
    lbl_804D7FFC = 1;
    lbl_804D7FF4 = 0;
    lbl_804D7FF0 = 2;
    return true;
}

void fn_80005E04() {
    switch (lbl_804D7FF0) {
        case 0:
            if (OSGetResetSwitchState() != 0) {
                lbl_804D7FF0 = 1;
            }
            fn_80005CF8();
            break;
        case 1:
            if (fn_80005CF8() != 0) {
                return;
            }

            if (OSGetResetSwitchState() == 1) {
                return;
            }
            
            lbl_804D7FF0 = 2;
            break;
        case 2:
            JUTGamePad::recalibrate(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
            sGamePad->stopMotor();
            fn_800083A4(2);
            fn_8018A78C(15);
            SceneManager::fn_8000B334(1);
            lbl_804D7FF0 = 3;
            break;
        case 3:
            break;
    }
}
