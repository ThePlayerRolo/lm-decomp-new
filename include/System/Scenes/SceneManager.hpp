#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "System/Scenes/Scene.hpp"

namespace SceneManager {
    u16 getFrameInterval();
    void requestSceneChange(SceneID); // Unsure of return type/args
    void mainLoop(); // Looks to be the main game loop or something similar?

    extern BOOL sSceneChangePending;
    extern s64 sTotalFrameCount;
    extern u64 sSceneFrameCount;
    extern SceneID sCurrSceneId;
    extern s32 lbl_804D80A4;
    extern BOOL lbl_804D80AC;
    extern s32 lbl_804D80B0; // Definitely not AppearPointSlot, will need to re-evaluate this.
}

#endif
