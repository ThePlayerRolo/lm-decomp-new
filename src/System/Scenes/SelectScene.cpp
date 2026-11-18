#include "System/Scenes/SelectScene.hpp"
#include "System/Scenes/MainGameScene.hpp"
#include "System/Scenes/OpeningScene.hpp"
#include "System/Scenes/SceneFunctionCalls.hpp"

#include "Unsorted/InGameFlagsUtil.hpp"
#include "Unsorted/LMDisplayUtil.hpp"

namespace SelectScene {
    static void fn_8000B978();
    static void init();
    static SceneID update();
    static void draw();
    static void destroy();

    Scene sSelectScene = {
        "SELECT", 
        1, 
        init, 
        update, 
        draw, 
        destroy
    };

    void fn_8000B8D8(MainGameSceneHelper* param_1) {
        param_1->_0 = 0;
        OSInitMessageQueue(&param_1->mMsgQueue, &param_1->mMsgSend, 1);
    }

    // Called when new game+ is activated?
    void fn_8000B910() {
        // Disables Luigi Meeting E. Gadd, Event01; Enables Toad Cutscene, Event16; 
        // Enables Foyer Chandelier fall behaviour; Removes Parlor Cutscene models.
        setFlagOn(1);

        // Disables the Parlor Door Ghost Laughter SE
        setFlagOn(3);

        // Disables the Foyer Gold Ghost event, Event07; Enables Luigi Model in Event01
        setFlagOn(4);

        // Allows the Hidden Mansion option to appear in Event08, E. Gadds Lab Event.
        setFlagOn(5);

        // Turned on in Event08 to load event10, first time in training room vs Event09, 
        //      repeat trips to training room.
        setFlagOn(6);

        // Turned in Event08 to stop E. Gadd from lecturing Luigi again.
        // Using this flag, the cutscene loading into the mansion is changed to E. Gadd waving.
        setFlagOn(7);

        // Turns on the flag that normall is turned on when tapping on the Angel Statues
        //  In the gallery, which woudl otherwise prevent event28 from progressing.
        setFlagOn(17);

        void* temp = fn_800739A4(0);
        //Something like: temp[0x16A] = temp[0x16A] | 2; 
    }

    void init() {
        lbl_804D80C0 = 0;
        fn_80066B9C();
        fn_800739A4(0);
        fn_800735FC();
        fn_800379F4(&lbl_803CDEB0);
        OpeningScene::sNextSceneID = SCENE_MAIN_GAME;
        fn_800626B0();
        MainGameScene::sCurMapNo = 2;
        fn_8004CED4();
    }

    SceneID update() {
        if (lbl_804D8060 != 0) {
            return SCENE_SELECT;
        }

        return fn_8004CF6C();
    }

    void draw() {
        fn_8004CFBC();
        fn_80008004();
    }

    void destroy() {
        fn_8004D014();
    }
}
