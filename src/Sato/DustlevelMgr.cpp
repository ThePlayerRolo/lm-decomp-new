#include "Sato/DustlevelMgr.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Sato/saGrainControl.hpp"
#include "dolphin/mtx.h"

u32 DustlevelMgr::fn_801300B8() {
    u32 result = 0;
    Vec* unk = *(Vec**)_90->_450;
    DustlevelControl* control = mControlList.mHead->mNext;
    DustlevelParam* head = control->mParams.mHead;

    DustlevelParam* node = head->mNext;
    if (node != head) {
        Vec diff;
        PSVECSubtract(unk, &node->_0C, &diff);
        f32 bestMagnitude = VECMag(&diff);
        if (bestMagnitude <= (f32)node->_18) {
            result = node->_1C;
        }

        node = node->mNext;
        if (node != control->mParams.mHead) {
            do {
                PSVECSubtract(unk, &node->_0C, &diff);
                f32 currentMagnitude = VECMag(&diff);
                if (currentMagnitude <= (f32)node->_18 && currentMagnitude < bestMagnitude) {
                    result = node->_1C;
                    bestMagnitude = currentMagnitude;
                }
                node = node->mNext;
            } while (node != control->mParams.mHead);
        }
    }

    return result;
}

BOOL DustlevelMgr::vt_0C(ToolDataRef*) { return true; }
BOOL DustlevelMgr::vt_10(ToolDataRef*) { return true; }

// It uses some stuff in BSS here but it something like that
void DustlevelMgr::fn_801303EC() {
    Koga::GameModeUtil::addJmpReceiver(this);
    mControls = new DustlevelControl[1];
    mParams = new DustlevelParam[30];
    this->init(30, 1);
}
