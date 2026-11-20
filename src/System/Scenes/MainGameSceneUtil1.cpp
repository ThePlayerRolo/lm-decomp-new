#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXCull.h>
#include <JSystem/JKernel/JKRExpHeap.hpp>

#include "System/Scenes/MainGameSceneUtil1.hpp"
#include "System/Memory.hpp"
#include "System/Scenes/MainGameSceneUtil2.hpp"
#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/SceneManager.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "System/Scenes/SelectScene.hpp"
#include "Unsorted/LMDisplayUtil.hpp"
#include "Unsorted/GamePad.hpp"
#include "Unsorted/80009B80.hpp"
#include "Unsorted/80008418.hpp"
#include "System/DataOnly.hpp"

#include "macros.h"
#include "types.h"

MainGameSceneHelper::MainGameSceneHelper() {
    SelectScene::fn_8000B8D8(this);
}

namespace MainGameScene {

    s32 lbl_804D80D0;
    s32 lbl_804D80D4;
    MainGameSceneHelper lbl_803A3B10;

    void fn_8000C36C(void* param_1, s32 param_2) {
        if (MainGameScene::lbl_804D80C4 == 0) {
            lbl_804D80D4 = param_2;
            if (lbl_803A3B10._0 == 0) {
                OSSendMessage(&lbl_803A3B10.mMsgQueue, param_1, OS_MESSAGE_NOBLOCK);
            }
        }
    }

    s32 fn_8000C3B8() {
        return lbl_804D80D0;
    }

    // Requires that fn_800AD39C and its resulting struct/class be decompiled more.
    void fn_8000C3C0() {
        FORCE_DONT_INLINE; // Needed to avoid inlining in fn_8000C49C
        s32 recvMsg = OSReceiveMessage(&lbl_803A3B10.mMsgQueue, lbl_803A3B10.mMsgReceive, OS_MESSAGE_NOBLOCK);
        if (recvMsg != 0) {
            if (fn_8000C8D8()) {
                // calls fn_800AD39C(0) around here and gets the 0x55 byte
                if (SceneManager::lbl_804D8098 <= 2) {
                    lbl_804D80C4 = 2;
                    lbl_804D8438 = 0;
                    fn_80007E60(1);
                    fn_8018A678(1);
                    fn_8018A2A0(0x3804);
                    lbl_804D80D0 = 0;
                    fn_8015FD68(&lbl_803D990C);
                    fn_8007220C();
                    lbl_803A3B10._0 = 1;
                }
            }
        }
    }

    void fn_8000C49C() {
        if (MainGameScene::lbl_804D80C4 == 0) {
            fn_8000C3C0();
            return;
        }
        else if (MainGameScene::lbl_804D80C4 == 2) {
            if (lbl_804D843C == 0 && lbl_804D80D0 == 0) {
                u8 oldGroup = setCurHeapGroupId(0x14);
                OSMessage msg = lbl_803A3B10.mMsgReceive;
                fn_80029BA4(msg, lbl_804D80D4);
                setCurHeapGroupId(0x18);
                fn_80121944();
                setCurHeapGroupId(oldGroup);
                lbl_804D80D0 = 1;
            }

            if (sGamePad->testTrigger(0xA00)) {
                fn_8000C6A8();
                return;
            }

            fn_80046864();
            fn_80160138(lbl_803D990C);
            
            switch (lbl_804D80D0) {
                case 0:
                    break;
                case 1:
                    if (fn_801219FC() == 0) {
                        lbl_804D80D0 = 2;
                    }
                    break;
                case 2:
                    fn_80029C38();
                    break;
            }
        }
    }

    void fn_8000C598() {
        switch (lbl_804D80D0) {
            case 0:
                break;
            case 1:
                fn_80009B80();
                fn_80008654(&lbl_803A3820);
                GXSetViewportJitter(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f, 1);
                GXSetScissor(0, 0, 640, 480);
                fn_80121AFC();
                break;
            case 2:
                fn_80008654(&lbl_803A3820);
                GXSetViewportJitter(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f, 1);
                GXSetScissor(0, 0, 640, 480);
                fn_80029FA0();
                fn_8002A17C();
                Mtx* pMtx = &lbl_803A3820._18C;
                fn_801604FC(lbl_803D990C, pMtx);
                fn_80045D18();
                break;
        }

        fn_8005DF84();
        fn_80046868();
        fn_80072230(6);
        fn_8003E7B0(0);
        fn_80072230(7);
    }

    void fn_8000C6A8() {
        if (lbl_804D80C4 == 2) {
            if (!fn_80029C08()) {
                return;
            }

            lbl_804D80C4 = 0;
            lbl_804D8438 = 1;
            fn_8018A2A0(0x1037);
            fn_8018A2A0(0x3804);
            fn_8018A678(0);
            fn_8002A1F4();
            fn_801219C4();
            fn_80188760(lbl_804D8008 & 0xFF, nullptr);
            fn_8005DAFC();
            fn_80007E60(2);

            lbl_804D80D0 = 0;
            lbl_803A3B10._0 = 0;
            fn_8015FD80(lbl_803D990C, &lbl_803A3B10);

            if (sUnusedHeap != nullptr) {
                sUnusedHeap->destroy();
            }
        }
    }
}
