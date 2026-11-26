#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSMessage.h>
#include <dolphin/os/OSReset.h>
#include <dolphin/dvd.h>
#include <JSystem/JUtility/JUTGamePad.hpp>

#include "System/Reset.hpp"
#include "System/DiscFile.hpp"
#include "System/BackgroundTask.hpp"
#include "System/Memory.hpp"
#include "System/DisplayUtil.hpp"
#include "System/ScreenTransitionCtrl.hpp"
#include "System/80009584.hpp"
#include "System/MathUtils.hpp"
#include "System/ResetGX.hpp"
#include "System/GameRender.hpp"

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
    SM_STATE_LOADING,
    SM_STATE_WAIT_TRANSITION,
    SM_STATE_RUNNING,
};

struct SceneManagerHelper {
    inline SceneManagerHelper();
    
    /* 0x00 */ SceneManagerState mState;
    /* 0x04 */ SceneID mSceneID;
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
    mState = SM_STATE_LOADING;
    OSInitMessageQueue(&mOSMsgQueue, &mMsgs, 1);
    OSReceiveMessage(&mOSMsgQueue, nullptr, 0);
}

namespace SceneManager {
    static void drawScene();
    static void updateScene();
    static void sceneLoop();
    
    BOOL sSceneChangePending;
    u64 sTotalFrameCount; // Never reset
    u64 sSceneFrameCount; // Resets ever scene change
    SceneID sCurrSceneId;
    MapNumber sNextMapNo;
    static BOOL sSceneEnd;
    BOOL sDiscErrorActive;
    s32 lbl_804D80B0;
    static s32 sUnusedSceneInt;
    static s32 lbl_804D80B8; // If set, would call fn_80188710

    static SceneManagerHelper sSceneMgr;
    static Scene* sCurrScene = &BootScene::sBootScene;

    u16 getFrameInterval() {
        return sCurrScene->mFrameInterval;
    }

    void requestSceneChange(SceneID param_1) {
        sSceneChangePending = 1;
        OSSendMessage(&sSceneMgr.mOSMsgQueue, (OSMessage)param_1, OS_MESSAGE_NOBLOCK);
    }

    void drawScene() {
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
        defaultOrthoView();
    }

    void updateScene() {
        SceneID val = sSceneMgr.mSceneID;
        if (SceneManager::sCurrSceneId != val) {
            SceneManager::sCurrSceneId = val;
            sSceneChangePending = 1;
            sSceneEnd = 1;
            ScreenTransitionCtrl::requestTransition();
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
        if (isDiscLoadPending() != true && sSceneMgr.mState == SM_STATE_RUNNING && 
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
            ScreenTransitionCtrl::requestTransition();
            sSceneEnd = 1;
        }
    }

    void sceneLoop() {
        sSceneMgr.mState = SM_STATE_LOADING;
        sSceneMgr.mSceneID = SceneManager::sCurrSceneId;

        while (true) {
            sUnusedSceneInt = 0;
            beginFrame();

            if (sSceneMgr.mState == SM_STATE_RUNNING) {
                drawScene();
            }

            sScreenTransitionCtrl.draw();
            setDVDStatus();

            switch (sSceneMgr.mState) {
                case SM_STATE_LOADING:
                    if (pollBackgroundTaskComplete() == 1) {
                        sSceneMgr.mState = SM_STATE_WAIT_TRANSITION;
                        setDirectionalRepeat(sCurrScene->mFrameInterval);
                        setFrameRateDivisor(sCurrScene->mFrameInterval);
                    }
                    break;
                case SM_STATE_WAIT_TRANSITION:
                    if (sScreenTransitionCtrl.getState() != 1) {
                        ScreenTransitionCtrl::setTransitionType(SCREEN_TRANSITION_BLACK_FADE);
                        sSceneMgr.mState = SM_STATE_RUNNING;
                        setCurHeapGroupId(0x16);
                    }
                    break;
            }

            fn_80185910();
            applyRenderMode();
            JUTGamePad::read();
            fn_80009580();

            if (sSceneMgr.mState == 2 && sDiscErrorActive == 0 && sSceneEnd == 0) {
                swapPerFrameBuffer();
                sSceneMgr.mSceneID = sCurrScene->mUpdateFn();
            }

            sScreenTransitionCtrl.update();
            if (BootScene::sBootReady != 0) {
                fn_8018865C();
            }

            if (lbl_804D80B8 != 0) {
                fn_80188710();
            }

            endFrame();
            if (sSceneMgr.mState != SM_STATE_LOADING) {
                sScreenTransitionCtrl.startTransitionIn();
            }

            if (sSceneEnd != 0) {
                sSceneEnd = 0;
                break;
            }

            updateScene();
            updateReset();
            sTotalFrameCount++;
            sSceneFrameCount++;
        }
    }

    void mainLoop() {
        initBackgroundTask();

        do {
            sSceneFrameCount = 0;

            randomReset();
            setCurHeapGroupId(0xC);
            initPerFrameBuffer();
            setCurHeapGroupId(0x1A);
            startBackgroundTask(sCurrScene->mInitFn);
            ScreenTransitionCtrl::setTransitionLength(30);
            sceneLoop();
            sCurrScene->mDestroyFn();
            freePerFrameBuffer();
            sCurrScene = sSceneTable[sCurrSceneId];
            freeHeapGroups(0x1A);
        } while (true);
    }
}
