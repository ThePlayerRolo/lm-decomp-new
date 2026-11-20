#include "System/Memory.hpp"
#include "System/Scenes/MovieScene.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "dolphin/os/OSCache.h"
#include "types.h"

namespace MovieScene {
    static void init();
    static SceneID update();
    static void draw();
    static void destroy();

    Scene sMovieScene = {
        "MOVIE", 
        2, 
        init, 
        update, 
        draw, 
        destroy
    };

    void init() {
        fn_8006722C();
        s32 gameHeapFree = getGameHeapFreeSize();
        u32 memDiff = gameHeapFree - 0x100000;
        void* newMem = allocMem(memDiff, 32);

        if (newMem != nullptr) {
            do {
                do {
                    // Some sort of struct creation step
                } while (true); // Not the correct condition but definitely some sort of loop
            } while (true); // Not the correct condition but definitely some sort of loop
        }
        
        DCStoreRange(newMem, memDiff);
        fn_8018C920("/movie/pikminS.h4m", newMem, memDiff);
    }

    SceneID update() {
        if (fn_800673E0()) {
            return SCENE_SELECT;
        }

        return SCENE_MOVIE;
    }

    void draw() {
        fn_80067420();
    }

    void destroy() {
        fn_8006775C();
    }
}
