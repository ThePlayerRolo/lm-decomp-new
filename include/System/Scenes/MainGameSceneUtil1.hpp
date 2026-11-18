#ifndef MAIN_GAME_SCENE_UTIL_1_HPP
#define MAIN_GAME_SCENE_UTIL_1_HPP

#include <dolphin/os/OSMessage.h>
#include <types.h>

struct MainGameSceneHelper {
    inline MainGameSceneHelper();

    /* 0x00 */ s32 _0;
    /* 0x04 */ OSMessageQueue mMsgQueue;
    /* 0x24 */ OSMessage mMsgSend;
    /* 0x28 */ OSMessage mMsgReceive;
};

namespace MainGameScene {
    // Unsure of return types/args
    void fn_8000C36C();
    s32 fn_8000C3B8();
    void fn_8000C49C();
    void fn_8000C598();
    void fn_8000C6A8();
}

#endif
