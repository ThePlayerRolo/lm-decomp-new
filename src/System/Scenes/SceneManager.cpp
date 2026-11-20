#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSMessage.h>
#include <dolphin/os/OSReset.h>
#include <dolphin/dvd.h>
#include <JSystem/JUtility/JUTGamePad.hpp>

#include "System/DiscFile.hpp"
#include "System/BackgroundTask.hpp"
#include "System/Memory.hpp"

#include "Unsorted/MathUtils.hpp"
#include "Unsorted/LMDisplayUtil.hpp"
#include "Unsorted/800080DC.hpp"

// Other Scene related stuff
#include "System/Scenes/SceneManager.hpp"
#include "System/Scenes/BootScene.hpp"
#include "System/Scenes/EndingScene.hpp"
#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/MovieScene.hpp"
#include "System/Scenes/OpeningScene.hpp"
#include "System/Scenes/Scene.hpp"
#include "System/Scenes/SelectScene.hpp"
#include "System/Scenes/StuffRollScene.hpp"
#include "System/Scenes/TitleScene.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"

enum SceneManagerState {
    SM_STATE_0,
    SM_STATE_1,
    SM_STATE_2
};

struct SceneManagerHelper {
    inline SceneManagerHelper();
    
    /* 0x00 */ SceneManagerState mState;
    /* 0x04 */ SceneID _4;
    /* 0x08 */ OSMessageQueue mOSMsgQueue;
    /* 0x28 */ OSMessage mMsgs;
}; // size 0x2C

static Scene* sSceneTable[SCENE_MAX] = {
    &BootScene::sBootScene,
    &TitleScene::sTitleScene,
    &MainGameScene::sMainGameScene,
    &SelectScene::sSelectScene,
    &OpeningScene::sOpeningScene,
    &StuffRollScene::sStuffRollScene,
    &EndingScene::sEndingScene,
    &MovieScene::sMovieScene,
};

SceneManagerHelper::SceneManagerHelper() {
    mState = SM_STATE_0;
    OSInitMessageQueue(&mOSMsgQueue, &mMsgs, 1);
    OSReceiveMessage(&mOSMsgQueue, nullptr, 0);
}

namespace SceneManager {
    static void fn_8000B370(); // Unsure of return type/args
    static void fn_8000B4A0(); // Unsure of return type/args
    static void fn_8000B610(); // Unsure of return type/args
    
    s32 lbl_804D8088;
    static s32 lbl_804D808C;
    s64 lbl_804D8090;
    u64 lbl_804D8098;
    SceneID sCurrSceneId;
    s32 lbl_804D80A4;
    static s32 lbl_804D80A8;
    s32 lbl_804D80AC;
    s32 lbl_804D80B0;
    static s32 lbl_804D80B4;
    static s32 lbl_804D80B8;

    static SceneManagerHelper sSceneMgr;
    static Scene* sCurrScene = &BootScene::sBootScene;

    u16 fn_8000B328() {
        return sCurrScene->_10;
    }

    void fn_8000B334(s32 param_1) {
        lbl_804D8088 = 1;
        OSSendMessage(&sSceneMgr.mOSMsgQueue, (OSMessage)param_1, OS_MESSAGE_NOBLOCK);
    }

    void fn_8000B370() {
        GXLoadPosMtxImm(sDefaultMtx, 0);
        GXLoadNrmMtxImm(sDefaultMtx, 0);

        GXLoadPosMtxImm(sDefaultMtx, 3);
        GXLoadNrmMtxImm(sDefaultMtx, 3);

        GXLoadPosMtxImm(sDefaultMtx, 6);
        GXLoadNrmMtxImm(sDefaultMtx, 6);

        GXLoadPosMtxImm(sDefaultMtx, 9);
        GXLoadNrmMtxImm(sDefaultMtx, 9);

        GXLoadPosMtxImm(sDefaultMtx, 12);
        GXLoadNrmMtxImm(sDefaultMtx, 12);

        GXLoadPosMtxImm(sDefaultMtx, 15);
        GXLoadNrmMtxImm(sDefaultMtx, 15);

        GXLoadPosMtxImm(sDefaultMtx, 18);
        GXLoadNrmMtxImm(sDefaultMtx, 18);

        GXLoadPosMtxImm(sDefaultMtx, 21);
        GXLoadNrmMtxImm(sDefaultMtx, 21);

        GXLoadPosMtxImm(sDefaultMtx, 24);
        GXLoadNrmMtxImm(sDefaultMtx, 24);

        GXLoadPosMtxImm(sDefaultMtx, 27);
        GXLoadNrmMtxImm(sDefaultMtx, 27);

        sCurrScene->mDrawFn();
        LMDefaultOrthoView();
    }

    void fn_8000B4A0() {
        SceneID val = sSceneMgr._4;
        if (SceneManager::sCurrSceneId != val) {
            SceneManager::sCurrSceneId = val;
            lbl_804D8088 = 1;
            lbl_804D80A8 = 1;
            fn_80008394();
        }

        if (fn_8018A8B4() == 2) {
            if (!fn_8018A860()) {
                return;
            }

            if (!DVDCheckDisk()) {
                GXDrawDone();
                while(fn_80185938() == 7) {};
                LCDisable();
                OSResetSystem(1, OS_RESET_RESTART, false);
                while(true) {};
            }
        }

        OSMessage msg;
        if (isDiscLoadPending() != true && sSceneMgr.mState == SM_STATE_2 && 
                (fn_8018A8B4() != 2 || (fn_8018A860() && !DVDGetDriveStatus())) && 
                OSReceiveMessage(&sSceneMgr.mOSMsgQueue, &msg, OS_MESSAGE_NOBLOCK)) {
            if (lbl_804D7FF0 == 3) {
                lbl_804D7FF0 = 0;
                if (!DVDCheckDisk()) {
                    GXDrawDone();
                    while(fn_80185938() == 7) {};
                    LCDisable();
                    OSResetSystem(1, OS_RESET_RESTART, false);
                    while(true) {};
                }
            }

            if (fn_8018A8B4() == 3) {
                fn_8018A8BC(0);
            }

            sCurrSceneId = static_cast<SceneID>(reinterpret_cast<u32>(msg));
            fn_80008394();
            lbl_804D80A8 = 1;
        }
    }

    void fn_8000B610() {
        sSceneMgr.mState = SM_STATE_0;
        sSceneMgr._4 = SceneManager::sCurrSceneId;

        while (true) {
            lbl_804D80B4 = 0;
            fn_80007800();

            if (sSceneMgr.mState == SM_STATE_2) {
                fn_8000B370();
            }

            fn_800081A8(&lbl_803A3810);
            setDVDStatus();

            switch (sSceneMgr.mState) {
                case SM_STATE_0:
                    if (pollBackgroundTaskComplete() == 1) {
                        sSceneMgr.mState = SM_STATE_1;
                        fn_80009540(sCurrScene->_10);
                        fn_80007E60(sCurrScene->_10);
                    }
                    break;
                case SM_STATE_1:
                    if (lbl_803A3810) {
                        fn_800083A4(2);
                        sSceneMgr.mState = SM_STATE_2;
                        setCurHeapGroupId(0x16);
                    }
                    break;
            }

            fn_80185910();
            fn_800079B0();
            JUTGamePad::read();
            fn_80009580();

            if (sSceneMgr.mState == 2 && lbl_804D80AC == 0 && lbl_804D80A8 == 0) {
                fn_8000ADCC();
                sSceneMgr._4 = sCurrScene->mUpdateFn();
            }

            fn_8000812C(&lbl_803A3810);
            if (BootScene::sBootReady != 0) {
                fn_8018865C();
            }

            if (lbl_804D80B8 != 0) {
                fn_80188710();
            }

            LMChangeFrameBuffer();
            if (sSceneMgr.mState != SM_STATE_0) {
                fn_800080DC(&lbl_803A3810);
            }

            if (lbl_804D80A8 != 0) {
                lbl_804D80A8 = 0;
                break;
            }

            fn_8000B4A0();
            fn_80005E04();
            lbl_804D8090++;
            lbl_804D8098++;
        }
    }

    void fn_8000B7F4() {
        initBackgroundTask();

        do {
            lbl_804D8098 = 0;

            randomReset();
            setCurHeapGroupId(0xC);
            fn_8000AD48();
            setCurHeapGroupId(0x1A);
            startBackgroundTask(sCurrScene->mInitFn);
            fn_800083B4(0x1E);
            fn_8000B610();
            sCurrScene->mDestroyFn();
            fn_8000ADA0();
            sCurrScene = sSceneTable[sCurrSceneId];
            freeHeapGroups(0x1A);
        } while (true);
    }
}
