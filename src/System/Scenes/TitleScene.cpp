#include "System/Scenes/TitleScene.hpp"
#include "System/BackgroundTask.hpp"
#include "System/Scenes/OpeningScene.hpp"
#include "System/Scenes/Scene.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "System/Scenes/SceneManager.hpp"

#include "System/Memory.hpp"
#include "Unsorted/800627D8.hpp"
#include "Unsorted/BackgroundMusic.hpp"
#include "Unsorted/GamePad.hpp"
#include "Unsorted/LMDisplayUtil.hpp"

namespace TitleScene {
    static void init();
    static SceneID update();
    static void draw();
    static void destroy();

    // Unsure of typings
    static s32 lbl_804d8130;
    static s32 lbl_804d8134;
    static s32 lbl_804d8138;
    static s32 lbl_804d813C;

    Scene sTitleScene = {
        "TITLE",
        1,
        init,
        update,
        draw,
        destroy
    };

    // May not be a TitleScene function.
    void fn_8000EC98() {
        fn_80005C00();
    }

    void init() {
        lbl_804d8138 = 60;
        SceneManager::lbl_804D80AC = 0;

        s32 gameHeapFree = getGameHeapFreeSize();
        void* newMem = allocMem(0, 0x4);

        if (gameHeapFree > 0) {
            do {
                do {
                    // Some sort of struct creation step
                } while (true); // Not the correct condition but definitely some sort of loop
            } while (true); // Not the correct condition but definitely some sort of loop
        }

        freeMem(newMem);
        setLuigiAppearPoint(0);
        fn_80188760(TITLE_SCENE_UNK1, nullptr);
        lbl_804d8134 = 1800;
        if (lbl_804d8130 != 0) {
            lbl_804d8130 = 2;
        }

        setCurHeapGroupId(2);
        if (lbl_804D8058 != 1) {
            fn_8003ADE0(0);
        } else {
            fn_8003ADE0(1);
        }

        setCurHeapGroupId(0x1A);
    }

    SceneID update() {
        switch (lbl_804d8130) {
            case 0:
                startBackgroundTask(fn_8000EC98);
                lbl_804d8130 = 1;
                break;
            case 1:
                fn_8003AE54();
                if (pollBackgroundTaskComplete() == 1) {
                    lbl_804d8130 = 2;
                }
                break;
            case 2:
                if (sGamePad->testTrigger(0x1100)) {
                    lbl_804d813C = 1;
                }

                if (lbl_804d813C != 0 && lbl_804d8138 <= 0) {
                    lbl_804d8130 = 3;
                    OpeningScene::sNextSceneID = SCENE_MAIN_GAME;
                    fn_8018A2A0(0x3802);
                    SceneManager::fn_8000B334(3);
                    LMUpdateProgressiveMode();
                    break;
                }

                if (fn_8003AE54() != 0 && lbl_804d8138 != 0) {
                        lbl_804d8138--;
                }
                break;
            case 3:
                break;
        }

        lbl_804d8134--;
        if (lbl_804d8134 != 0) {
            return SCENE_TITLE;
        }

        OpeningScene::sNextSceneID = SCENE_TITLE;
        SceneManager::fn_8000B334(4);
        return SCENE_TITLE;
    }

    void draw() {
        fn_8003AE7C();
        fn_80007F90();
    }

    void destroy() {
        fn_80188D0C(0x1E);
        fn_8003AEA0();
    }
}
