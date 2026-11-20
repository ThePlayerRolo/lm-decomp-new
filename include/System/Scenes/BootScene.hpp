#ifndef BOOT_SCENE_HPP
#define BOOT_SCENE_HPP

#include "System/Scenes/Scene.hpp"

namespace BootScene {
    u8* getStaticDataArr();

    extern Scene sBootScene;
    extern s32 sBootReady;
};

#endif
