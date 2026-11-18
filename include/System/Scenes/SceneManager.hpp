#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "System/Scenes/Scene.hpp"

namespace SceneManager {
    u16 fn_8000B328();
    void fn_8000B334(s32); // Unsure of return type/args
    void fn_8000B7F4(); // Looks to be the main game loop or something similar?

    extern s32 lbl_804D8088;
    extern s64 lbl_804D8090;
    extern u64 lbl_804D8098;
    extern SceneID sCurrSceneId;
    extern s32 lbl_804D80A4;
    extern s32 lbl_804D80AC;
    extern s32 lbl_804D80B0; // Definitely not AppearPointSlot, will need to re-evaluate this.
}

#endif
