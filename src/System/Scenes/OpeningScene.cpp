#include "System/Scenes/OpeningScene.hpp"
#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/Scene.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "Unsorted/InGameFlagsUtil.hpp"

namespace OpeningScene {
    static void init();
    static SceneID update();
    static void draw();
    static void destroy();

    Scene sOpeningScene = {
        "OPENING",
        2,
        init,
        update,
        draw,
        destroy
    };

    static s32 sDemoID = 76;
    SceneID sNextSceneID = SCENE_MAIN_GAME;

    void init() {
        if (sNextSceneID == SCENE_MAIN_GAME) {
            // Flag 7 is turned on in event08 after E. Gadd's initial speech, so maybe
            //      this is knowing what opening movie to use as luigi loads in?
            if (getFlagValue(7)) {
                sDemoID = 0;
            } else {
                sDemoID = 76;
            }
        } else {
            sDemoID = 76;
        }

        fn_8005DAC4();

        if (sDemoID == 0) {
            fn_80188FB0(0xC0000000);
        } else {
            fn_80188FB0(0xC0000001);
        }

        while(!fn_80189054()) {};
        fn_80115264();
        fn_80114A38(sDemoID);
    }

    SceneID update() {
        switch (lbl_804D8D18) {
            case 2:
                fn_80114C00();
                fn_801891B4(0);
                lbl_804D8D18 = 4;
                break;
            case 4:
                if (fn_80114C70()) {
                    MainGameScene::sCurMapNo = 2;
                    return sNextSceneID;
                }
                break;
        }
        return SCENE_OPENING;
    }


    void draw() {
        if (lbl_804D8D18 == 4) {
            fn_80114E18();
        }
    }

    void destroy() {
        lbl_804D8D18 = 0;
        fn_80188D0C(0);
        fn_801151DC();
    }
}
