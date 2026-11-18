#include "System/Scenes/StuffRollScene.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"
#include "System/DiscFile.hpp"

namespace StuffRollScene {
    static void init();
    static SceneID update();
    static void draw();
    static void destroy();
    
    Scene sStuffRollScene = {
        "STUFFROLL", 
        1, 
        init, 
        update, 
        draw, 
        destroy
    };

    void init() {
        fn_8000F728();
    }

    SceneID update() {
        if (fn_8000F874() != 0) {
            return SCENE_ENDING;
        }

        return SCENE_STUFF_ROLL;
    }

    void draw() {
        fn_8000FB58();
    }

    void destroy() {
        while (isDiscLoadPending()) {};
    }
}
