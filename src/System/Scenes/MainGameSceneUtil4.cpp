#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXCull.h>
#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <JSystem/JUtility/JUTGamePad.hpp>

#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/MainGameSceneUtil4.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "System/DataOnly.hpp"
#include "System/DisplayUtil.hpp"
#include "System/80009584.hpp"


namespace MainGameScene {
    static s32 lbl_804D80E8;
    static BOOL lbl_804D80EC;

    void fn_8000CC18() {
        lbl_804D8438 = 0;
        setFrameRateDivisor(FRAME_INTERVAL_60FPS);
        fn_8018A2A0(0x3804);
        fn_8007220C();
        fn_80055114(lbl_804D80E8);
        lbl_804D80EC = 1;
    }

    void fn_8000CC60() {
        if (lbl_804D80C4 == 5) {
            if (lbl_804D80EC == 0) {
                lbl_804D8438 = 0;
                setFrameRateDivisor(FRAME_INTERVAL_60FPS);
                fn_8018A2A0(0x3804);
                fn_8007220C();
                fn_80055114(lbl_804D80E8);
                lbl_804D80EC = 1;
                return;
            }
            
            if (fn_80055270() != 0) {
                fn_8018A2A0(0x3804);
                fn_8000CD0C();
            }
        }
    }
    
    void fn_8000CCDC() {
        if (lbl_804D80EC != 0) {
            fn_8005DF84();
            fn_80055294();
        }
    }
    
    void fn_8000CD0C() {
        lbl_804D80C4 = 0;
        lbl_804D8438 = 1;
        fn_80055338();
        fn_80188760(lbl_804D8008 & 0xFF, nullptr);
        setFrameRateDivisor(FRAME_INTERVAL_30FPS);
        lbl_804D80EC = 0;
    }
    
    void fn_8000CD60() {
        static BOOL lbl_804D80F0 = 0;

        if (lbl_804D80C4 != 6) {
            return;
        }

        if (lbl_804D80F0 != 0) {
            lbl_804D80F0 = 0;
            lbl_804D80C4 = 0;
            fn_80187214();
            return;
        }

        if (sGamePad->testButton(JUTGamePad::B)) {
            lbl_804D80F0 = 1;
        }

        fn_80187218();
    }

    void fn_8000CDE0() {
        static BOOL lbl_804D80F8 = 0;

        if (lbl_804D80C4 != 7) {
            return;
        }

        if (lbl_804D80F8 != 0) {
            lbl_804D80F8 = 0;
            lbl_804D80C4 = 0;
            fn_800518A0();
            return;
        }

        if (fn_800517D8() != 0) {
            lbl_804D80F8 = 1;
        }
    }
}
