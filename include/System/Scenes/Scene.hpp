#ifndef SCENE_HPP
#define SCENE_HPP

#include <types.h>

#define MAX_SCENE_NAME_SIZE 16

enum SceneID {
    SCENE_BOOT,
    SCENE_TITLE,
    SCENE_MAIN_GAME,
    SCENE_SELECT,
    SCENE_OPENING,
    SCENE_STUFF_ROLL,
    SCENE_ENDING,
    SCENE_MOVIE,
    SCENE_MAX,
};

typedef void (*SceneInitFunc)();
typedef SceneID (*SceneUpdateFunc)();
typedef void (*SceneDrawFunc)();
typedef void (*SceneDestroyFunc)();

struct Scene {
    /* 0x00 */ char mName[MAX_SCENE_NAME_SIZE];
    /* 0x10 */ u16 _10;
    /* 0x14 */ SceneInitFunc mInitFn;
    /* 0x18 */ SceneUpdateFunc mUpdateFn;
    /* 0x1C */ SceneDrawFunc mDrawFn;
    /* 0x20 */ SceneDestroyFunc mDestroyFn;
};

#endif
