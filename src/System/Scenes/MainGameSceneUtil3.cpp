#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXCull.h>
#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <JSystem/JUtility/JUTGamePad.hpp>

#include "System/Scenes/SceneManager.hpp"
#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/MainGameSceneUtil2.hpp"
#include "System/Scenes/MainGameSceneUtil3.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "System/DataOnly.hpp"
#include "System/Memory.hpp"
#include "System/DisplayUtil.hpp"
#include "System/ResetGX.hpp"
#include "System/80008418.hpp"
#include "System/80009584.hpp"

namespace MainGameScene {
    s32 lbl_804D80E0;

    // requires fn_800AD39C to be more decompiled
    void fn_8000C90C() {
        if (lbl_804D80E0 != 0) {
            return;
        }

        if (fn_8000C8D8() && sGamePad->testTrigger(JUTGamePad::Z) && SceneManager::sSceneFrameCount >= 2) {
            switch (MainGameScene::sCurMapNo) {
                case MAP_GALLERY:
                case MAP_MANSION:
                    void* temp = fn_800AD39C(0); //checks against the 0x55 byte
                    lbl_804D80C4 = 3;
                    lbl_804D8438 = 0;
                    setFrameRateDivisor(FRAME_INTERVAL_60FPS);
                    fn_8018A678(1);
                    fn_8018A2A0(0x3804);
                    lbl_804D80E0 = 1;
                    fn_8007220C();
                    setIntRenderModeVFilter(0x10);
                    fn_800531B8();
                    break;
            }
        }
    }

    void fn_8000C9EC() {
        if (lbl_804D80C4 == 0) {
            fn_8000C90C();
            return;
        }
        else if (lbl_804D80C4 == 3) {
            if (lbl_804D843C == 0 && lbl_804D80E0 == 1) {
                fn_80121944();
                lbl_804D80E0 = 2;
            }

            if (sGamePad->testTrigger(JUTGamePad::B | JUTGamePad::Z)) {
                fn_8000CB78();
                return;
            }

            fn_80046864();
            
            switch (lbl_804D80E0) {
                case 1:
                    break;
                case 2:
                    if (fn_801219FC() == 0) {
                        lbl_804D80E0 = 3;
                    }
                    break;
                case 3:
                    fn_80053224();
                    break;
            }
        }
    }

    void fn_8000CAA0() {
        switch (lbl_804D80E0) {
            case 1:
                break;
            case 2:
                resetGXState();
                lbl_803A3820.fn_80008654();
                GXSetViewportJitter(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f, 1);
                GXSetScissor(0, 0, 640, 480);
                fn_80121AFC();
                break;
            case 3:
                lbl_803A3820.fn_80008654();
                GXSetViewportJitter(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f, 1);
                GXSetScissor(0, 0, 640, 480);
                fn_80121AFC();
                break;
        }

        fn_8005DF84();
        fn_8003E7B0(0);
    }
    
    void fn_8000CB78() {
        if (lbl_804D80E0 != 0 && lbl_804D80C4 == 3) {
            SceneManager::sSceneChangePending = FALSE;
            lbl_804D80E0 = 0;
            lbl_804D80C4 = 0;
            lbl_804D8438 = 1;
            fn_8018A678(0);
            fn_8018A2A0(0x1037);
            fn_8018A2A0(0x3804);
            fn_8005332C();
            fn_801219C4();
            fn_80188760(lbl_804D8008 & 0xFF, 0);
            fn_8005DAFC();
            setFrameRateDivisor(FRAME_INTERVAL_30FPS);
            setIntRenderModeVFilter(6);

            if (sUnusedHeap != nullptr) {
                sUnusedHeap->destroy();
            }
        }
    }
}
