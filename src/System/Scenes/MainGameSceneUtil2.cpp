#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/SceneManager.hpp"
#include "System/Scenes/MainGameSceneUtil2.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "Unsorted/GamePad.hpp"
#include "Unsorted/LMDisplayUtil.hpp"

namespace MainGameScene {
    s32 lbl_804D80D8;

    s32 fn_8000C784(void*, s32 param_1) {
        if (lbl_804D80C4 == 0 && SceneManager::lbl_804D8088 == 0 && 
            sGamePad->testTrigger(0x1000)) {
            
            lbl_804D80C4 = 1;
            lbl_804D8438 = 0;
            fn_80007E60(1);
            fn_8018A678(1);
            fn_8018A2A0(0x3804);
            fn_8007220C();
            lbl_804D80D8 = 1;
            return 2;
        }

        if (param_1 != 1) {
            return 2;
        }

        if (lbl_804D80D8 == 1) {
            fn_800391D4();
            lbl_804D80D8 = 0;
        }

        return fn_80039304();
    }

    void fn_8000C834() {
        if (lbl_804D80D8 != 1) {
            fn_80039328();
        }
    }

    void fn_8000C860() {
        fn_8018A678(0);
        lbl_804D8438 = 1;
        fn_80007E60(2);
    }

    void fn_8000C894() {
        SceneManager::lbl_804D8088 = 0;
        lbl_804D80C4 = 0;
        fn_8018A678(0);
        lbl_804D8438 = 1;
        fn_80007E60(2);
        fn_800393CC();
    }

    bool fn_8000C8D8() {
        if (lbl_803A3810 != 0) {
            return false;
        }

        if (SceneManager::lbl_804D8088 != 0) {
            return false;
        }

        return true;
    }
}
