#ifndef CHARACTER_COLLISION_MANAGER_HPP
#define CHARACTER_COLLISION_MANAGER_HPP

#include <types.h>
#include <JSystem/JORReflexible.hpp>

#include "MR/Array.hpp"

// TODO Maybe this TU is bigger, unsure

struct unkCharactColStruct1 {
    /* 0x00 */ s32 _0;
    /* 0x04 */ f32 _4;
    /* 0x08 */ f32 _8; //Unknown type;
    /* 0x0C */ f32 _C;
    /* 0x10 */ f32 _10; //Unknown type;
};

struct unkCharactColStruct3 {
    /* 0x00 */ f32 _0;
    /* 0x04 */ f32 _4;
    /* 0x08 */ f32 _8; //Unknown type;
    /* 0x0C */ f32 _C;
    /* 0x10 */ f32 _10; //Unknown type;
};

struct unkCharactColStruct4 {
    /* 0x00 */ f32 _0;
    /* 0x04 */ f32 _4;
    /* 0x08 */ f32 _8;
    /* 0x0C */ f32 _C; //Unknown type;
    /* 0x10 */ f32 _10; //Unknown type;
    /* 0x14 */ f32 _14; //Unknown type;
};

struct unkCharactColStruct2 {
    /* 0x00 */ unkCharactColStruct1 _0;
    /* 0x14 */ unkCharactColStruct3 _14;
    /* 0x28 */ unkCharactColStruct4 _28;
};

#define MAX_CHARACTER_COL 381

struct unkCharactColStruct5 {
    /* 0x00 */ s32 _0;
    /* 0x04 */ unkCharactColStruct1* _4;
    /* 0x08 */ u32 _8;
    /* 0x0C */ unkCharactColStruct3* _C;
    /* 0x10 */ unkCharactColStruct4* _10;

    // TODO These definitely don't belong here, but for now can stay.
    static unkCharactColStruct5* lbl_8038E118[MAX_CHARACTER_COL+1];
    static unkCharactColStruct5* lbl_8038DD00[]; // Indexed by Group IDs from ActorData
};

// TODO Maybe a better name here
class CharacterColElement {
    public:
        CharacterColElement();
        void init(s32);
        ~CharacterColElement();

    /* Size: 0xEC */
    private:
        /* 0x00 */ unkCharactColStruct5 _0;
        /* 0x14 */ u32 mGroupID;
        /* 0x18 */ u8 _18;
        /* 0x1C */ MR::AssignableArray<unkCharactColStruct1, 8> _1C;
        /* 0xC0 */ unkCharactColStruct3 _C0;
        /* 0xD4 */ unkCharactColStruct4 _D4;
};

class CharacterColManager : public JORReflexible {
public:
    CharacterColManager();
    /* 0x08 */ virtual ~CharacterColManager();
    inline CharacterColElement* begin() { return &_4[0]; }
    inline CharacterColElement* last() { return &_4[MAX_CHARACTER_COL - 1]; }
    inline CharacterColElement* end() { return &_4[MAX_CHARACTER_COL]; }

public:
    /* 0x04 */ CharacterColElement* _4;
};

#endif
