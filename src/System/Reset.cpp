#include <dolphin/os/OSFastCast.h>
#include <dolphin/os/OSResetSW.h>
#include <JSystem/JUtility/JUTGamePad.hpp>
#include <dolphin/pad.h>

#include "System/Reset.hpp"
#include "System/800080DC.hpp"
#include "System/DisplayUtil.hpp"
#include "Unsorted/GamePad.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "System/Scenes/SceneManager.hpp"

struct ResetThread {
    /* 0x000 */ OSThread mThread;
    /* 0x310 */ OSMessageQueue mMsgQueue;
    /* 0x330 */ OSMessage mMsg;
};

enum ResetState {
    RESET_STATE_IDLE,
    RESET_STATE_PRESSED,
    RESET_STATE_REQUESTED,
    RESET_STATE_RESETTING,
};

ResetState sResetState;
u8 sResetThreadStack[0x4000];
ResetThread sResetThread;

static void createResetThread(ResetThread*);

void initReset() {
    sResetState = RESET_STATE_IDLE;
    createResetThread(&sResetThread);
}

void* resetThreadMain(void*) {
    OSInitFastCast();
    while (true) {
        OSReceiveMessage(&sResetThread.mMsgQueue, nullptr, OS_MESSAGE_BLOCK);
    }
}

void createResetThread(ResetThread* pThread) {
    OSInitMessageQueue(&pThread->mMsgQueue, &pThread->mMsg, 1);
    u32 size = sizeof(sResetThreadStack);
    OSCreateThread(&pThread->mThread, resetThreadMain, nullptr, &sResetThreadStack[size], size, 1, 1);
    OSResumeThread(&pThread->mThread);
}

s32 checkResetPressed() {
    static u32 heldFrames = 0;
    static s32 resetRequested = 0;

    if (!sGamePad->testButton(JUTGamePad::START)) {
        resetRequested = 0;
        heldFrames = 0;
        return false;
    }
    
    if (!sGamePad->testButton(JUTGamePad::B)) {
        resetRequested = 0;
        heldFrames = 0;
        return false;
    }
    
    if (!sGamePad->testButton(JUTGamePad::X)) {
        resetRequested = 0;
        heldFrames = 0;
        return false;
    }
    
    if (resetRequested != 0) {
        return false;
    }

    heldFrames += 1;

    if (heldFrames < 30 / getFrameRateDivisor()) {
        return false;
    }
    
    resetRequested = 1;
    heldFrames = 0;
    sResetState = RESET_STATE_REQUESTED;
    return true;
}

void updateReset() {
    switch (sResetState) {
        case RESET_STATE_IDLE:
            if (OSGetResetSwitchState() != 0) {
                sResetState = RESET_STATE_PRESSED;
            }
            checkResetPressed();
            break;
        case RESET_STATE_PRESSED:
            if (checkResetPressed() != 0) {
                return;
            }

            if (OSGetResetSwitchState() == 1) {
                return;
            }
            
            sResetState = RESET_STATE_REQUESTED;
            break;
        case RESET_STATE_REQUESTED:
            JUTGamePad::recalibrate(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
            sGamePad->stopMotor();
            fn_800083A4(2);
            fn_8018A78C(15);
            SceneManager::fn_8000B334(1);
            sResetState = RESET_STATE_RESETTING;
            break;
        case RESET_STATE_RESETTING:
            break;
    }
}
