#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/Scene.hpp"

namespace MainGameScene {
    static SceneID update();
    static void fn_8000BB98(); // Uncertain of return types/args
    static void fn_8000BCE8(); // Uncertain of return types/args
    static void draw();
    static void destroy();
    static void fn_8000BFF0(); // Uncertain of return types/args
    static void fn_8000C078(); // Uncertain of return types/args
    static void init();
    static void fn_8000C2D0(); // Uncertain of return types/args

    Scene sMainGameScene = {
        "MAIN GAME",
        2,
        init,
        update,
        draw,
        destroy
    };

    s32 lbl_804D80C4;
    s32 sCurMapNo;
}
