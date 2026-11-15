#include <version.h>
#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <JSystem/JKernel/JKRMemArchive.hpp>
#include <JSystem/J2D/J2DPicture.hpp>
#include <JSystem/J2D/J2DOrthoGraph.hpp>
#include <dolphin/gx.h>

#include "System/Scenes/BootScene.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "System/Scenes/SceneManager.hpp"

#include "System/Memory.hpp"
#include "System/BackgroundTask.hpp"
#include "System/DiscFile.hpp"
#include "System/Yay0.hpp"

#include "Unsorted/LMDisplayUtil.hpp"
#include "Unsorted/staticDataAramData.h"
#include "Unsorted/80008418.hpp"
#include "Unsorted/80009B80.hpp"
#include "macros.h"

enum BootSceneState {
    BOOT_IDLE,
    BOOT_LOADING,
    BOOT_READY,
};

//.data
dummy_float_data()
enemies_float_data()

//NOTE: Files are created during setup
#if VERSION == VERSION_USA
// Archive is 0xDD380, but the rest is padding / reused, as it doubles as another buffer later on.
static u8 staticdata_usa_arc[0xE1000] ATTRIBUTE_ALIGN(32) = {
#include "staticdata_usa_arc.inc"
};
#define STATIC_DATA staticdata_usa_arc
#else
static u8 staticdata_arc[0xE1000] ATTRIBUTE_ALIGN(32) = {
#include "staticdata_arc.inc"
};
#define STATIC_DATA staticdata_arc
#endif

static GXColor sLogoMatColor = { 255, 255, 255, 32 }; // White

namespace BootScene {
    static void dvdFileOpenCallback(void*, DiscFileInfo*);
    static void loadStaticDataArchives();
    static void loadStaticData();
    static void init();
    static void destroy();
    static SceneID update();
    static void draw();

    Scene sBootScene = {
        "BOOT", 
        1, 
        init, 
        update, 
        draw, 
        destroy
    };

    // needs to be here for position
    const char* ninLogoFileName = "/ninlogo.pcm";

    s32 sBootReady;
    static BootSceneState sBootSceneState;
    static u16 lbl_804D8118;
    static f32 lbl_804D811C;
    static J2DPicture* nintendoLogoPicture;
    static JKRMemArchive* staticDataArchive;

    void dvdFileOpenCallback(void* param_1, DiscFileInfo* param_2) {
        u8* block = reinterpret_cast<u8*>(JKRAllocFromHeap(nullptr, getYay0ArcSize(param_2->mFileBuffer), 32));
        decompressYay0(param_2->mFileBuffer, block);
        freeMem(param_2->mFileBuffer);
        fn_80066FAC(new JKRMemArchive(block, 0, MBF_0));
    }

    void loadStaticDataArchives() {
        setCurHeapGroupId(16);
        becomeGameHeapCurrent();
        void* game_usaData = openDiscFileAsync("/Game/game_usa.szp", BootScene::dvdFileOpenCallback, nullptr, nullptr);
        sSystemHeap->becomeCurrentHeap();
        setCurHeapGroupId(3);
        u8* data = (u8*)staticDataArchive->getResource("/res_titl.szp");

        sResTitleAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            staticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)staticDataArchive->getResource("/gameboy.szp");

        sGameboyAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            staticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)staticDataArchive->getResource("/guidemap.szp");

        sGuidemapAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            staticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)staticDataArchive->getResource("/res_paus.szp");

        sResPauseAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            staticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)staticDataArchive->getResource("/res_list.szp");

        sResListAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            staticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        while (isDiscLoadPending()) {}
    }

    void loadStaticData() {
        sSystemHeap->changeGroupID(4);
        fn_80188594(JKRAllocFromHeap(sSystemHeap, 0xC0000, 0x20), 0xC0000, 0xF00000);
        fn_8004D4C8();
        fn_80188714(staticDataArchive->getResource("/ninlogo.pcm"));
        BootScene::loadStaticDataArchives();
        fn_80188638();
        do { } while(fn_80188740() == true);
    }

    // problems but can't create a scratch because tu is too big lol
    void init() {
        sBootSceneState = BOOT_IDLE;
        sBootReady = 0;
        sSystemHeap->becomeCurrentHeap();
        fn_80009490();
        fn_8005FD80();
        setCurHeapGroupId(8);
        fn_8003EB44();
        setCurHeapGroupId(26);
        lbl_804D8118 = 0;
        lbl_804D811C = 0.0f;
        sLogoMatColor.a = 32;

        staticDataArchive = new JKRMemArchive(STATIC_DATA, 0, MBF_0);

        u8* nintendoSzpBlock = reinterpret_cast<u8*>(staticDataArchive->getResource("/nintendo.szp"));
        u32 size = getYay0ArcSize(nintendoSzpBlock);
        becomeGameHeapCurrent();
        JUTTexture* data = reinterpret_cast<JUTTexture*>(allocMem(size, 0x20));
        getSystemHeap()->becomeCurrentHeap();
        decompressYay0(nintendoSzpBlock, (u8*)data);
        nintendoLogoPicture = new J2DPicture(data);
    }

    void destroy() {
        delete nintendoLogoPicture;
        staticDataArchive->unmount();
        becomeGameHeapCurrent();
    }

    SceneID update() {
        u32 ret;
        switch (sBootSceneState) {
        case BOOT_IDLE:
            startBackgroundTask(loadStaticData);
            fn_80007F28();
            sBootSceneState = BOOT_LOADING;
            return SCENE_BOOT;
        case BOOT_LOADING:
            if (pollBackgroundTaskComplete() == 0) {
                return SCENE_BOOT;
            }
            sBootReady = 1;
            sBootSceneState = BOOT_READY;
            return SCENE_BOOT;
            break;
        default:
            return SCENE_TITLE;
        }
    }

    // problems but can't create a scratch because tu is too big lol
    void draw() {
        static s32 bootSceneFrameCount = 0;
        
        fn_80009B80();
        fn_80008654(&lbl_803A3820);
        GXSetChanMatColor(GX_COLOR0A0, sLogoMatColor);
        LMSetViewportJitter(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        GXSetScissor(0, 0, 640, 480);
        GXSetCurrentMtx(0);
        GXSetNumChans(1);
        GXSetNumTevStages(1);
        Mtx mtx;
        u16 temp = lbl_804D8118;
        fn_8000A40C(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, mtx, 0, 0, temp);
        PSMTXConcat(lbl_803A3820._18C, mtx, mtx);
        GXLoadNrmMtxImm(mtx, 0);
        temp = lbl_804D8118;
        fn_8000A40C(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, lbl_804D811C, mtx, 0, 0, temp);
        PSMTXConcat(lbl_803A3820._18C, mtx, mtx);
        GXLoadNrmMtxImm(mtx, 0);
        J2DOrthoGraph graph(0, 0, 640, 480);
        graph.setPort();
        GXColor color = (GXColor){ 220, 0, 0, 255};
        nintendoLogoPicture->mBlack = sBlack;
        nintendoLogoPicture->mWhite = color;
        nintendoLogoPicture->draw(0, 0, 640, 480, false, false, false);
        if (SceneManager::lbl_804D8098 >= 2) {
            fn_80007E50(1);
        }
        if (sBootSceneState == BOOT_READY) {
            bootSceneFrameCount++;
        }
    }

    u8* getStaticDataArr() {
        return STATIC_DATA;
    }

}
