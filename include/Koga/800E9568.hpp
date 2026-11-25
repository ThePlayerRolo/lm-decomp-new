#ifndef KOGA_800E9568_HPP
#define KOGA_800E9568_HPP

#include <types.h>
#include <JSystem/JGeometry/JGVec3.hpp>

#include "Sato/EnThought.hpp"

namespace Koga {
    class CharacterEvent;
}

class EnThought;
class Character;
class Player;

enum CharacterState {
    /* 0 */ DEFAULT_CHARSTATE,
    /* 1 */ CHARSTATE_1,
    /* 2 */ CHARSTATE_2
};

class unkEnManager1 {
public:
    unkEnManager1();
    ~unkEnManager1();

    /* 0x0 */ EnThought* _0;
    /* 0x4 */ CharacterState mState;
    /* 0x8 */ u32 _8;
    /* 0xC */ u8 _C;

    void fn_800E9A0C(EnThought*);
    bool fn_800E9A58(s32);
    void fn_800E9ACC();

    void fn_800E9B44();
    void fn_800E9B74();
    bool fn_800E9C38(Koga::CharacterEvent*);

    bool fn_800E9C78();
    Character* getCharacter();
    void fn_800E9CDC(); // Something to do with invisible Character.
    void* fn_800E9F90();
};

struct unkEnManager1Wrapper {
    unkEnManager1* mBegin;
    unkEnManager1* mEnd;
};


// Return types or argument types could be wrong.
Vec* fn_800E9568(s32);
s32 fn_800E9594(s32);
BOOL fn_800E95C0(s32, JGeometry::TVec3f*, u16*);
s32 fn_800E96B8(JGeometry::TVec3f*, JGeometry::TVec3f*, f32);
s32 fn_800E96E8(JGeometry::TVec3f*, JGeometry::TVec3f*);
s32 fn_800E971C(JGeometry::TVec3f*, JGeometry::TVec3f*);
Player* getPlayer(s32);
s32 fn_800E977C(s32, s32);
void fn_800E97B0(s32);
Character* fn_800E97DC(char*); // Gets something from ToolData by CodeName
void fn_800E98E0(unkEnManager1Wrapper*);
BOOL fn_800E9914(const char*, s32); //Probably some sort of static function
s32 fn_800E9948(const char*);
s32 fn_800E9974(const char*);
void fn_800E99A0();
void fn_800E9DC8();
void fn_800E9E04();
void fn_800E9E48();
void fn_800E9E8C();
void fn_800E9ED0();
void fn_800E9F08();
void fn_800E9F5C();
void fn_800E9F90();
void fn_800E9FCC();
void fn_800EA0A8();
void fn_800EA0E0();
void fn_800EA134();
void fn_800EA174();


#endif
