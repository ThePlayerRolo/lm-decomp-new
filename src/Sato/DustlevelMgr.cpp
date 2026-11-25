#include "Sato/DustlevelMgr.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Sato/saGrainControl.hpp"
#include <dolphin/mtx.h>

u16* fn_8001CEAC(u32, u32);
void fn_80127C08();

void Dust::fn_8012fc50() {
    if (_458 != 0) return;
    fn_8012E350();

    DustUnk2* current = _220.mHead->mNext;
    if (current != _220.mHead) {
        do {
            DustUnk2* next = current->mNext;
            if ((*fn_8001CEAC(current->_30, 0) & 1) == 0) {
                current->_3D = 0;
            }

            if (fn_8012F9C8(current) == 1) {
                current = current->mNext;
            } else {
                current = next;
            }
        } while (current != _220.mHead);
    }

    fn_80127C08();
}

u32 DustlevelMgr::fn_801300B8() {
    u32 result = 0;
    Vec* unk = _90->_450->mPos;
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
    init(30, 1);
}
