#ifndef EN_MANAGER_HPP
#define EN_MANAGER_HPP

#include <types.h>
#include <JSystem/JGeometry/JGVec3.hpp>
#include <JSystem/JORReflexible.hpp>

#include "Koga/Message.hpp"
#include "Koga/800E9568.hpp"
#include "Koga/ToolData.hpp"
#include "MR/Array.hpp"
#include "dolphin/mtx.h"

class EnemyStrategy;
class EnThought;
class JKRArchive;

namespace Koga {
    class EnManager;
    class EnTypesManager;
    class CharacterEvent;
}

// Fabricated name, subject to change
class AppearPointSlot {
public:
    void init(Vec*, Koga::ToolData*, int);
    void fn_800E616C(Vec*);

    /* 0x0 */ s32 _0;
    /* 0x4 */ Koga::ToolData* _4;
    /* 0x8 */ s32 _8;
    /* 0xC - 0x13 */ Vec mPosition;
    /* 0x18 */ u32 _18;
};

class unkEnManager2 {
public:
    unkEnManager2();
    unkEnManager2(const ToolDataRef&);

    u32 fn_800E601C(); 
    const char* getCreateName();
    ToolDataRef fn_800E6134();

    /* 0x0 - 0x7 */ ToolDataRef mCharacter;
    s32 _8; //mTypeIndex?
};

namespace Koga {

    class EnManager : public JORReflexible, public MessageReceiver {
    public:
        EnManager(); // This is wrong because TVec3f gives a constructor that shouldn't be there. Maybe 3 f32's instead.
        /* 0x08 */ virtual ~EnManager();

        void loadCharacterInfo(JKRArchive*);
        void fn_800E46C0(); // Needs more functions decompiled

        // Gets called by JmpMessageSender, also seems to create CharacterEvents to active slots?
        void fn_800E4800(char*); // Could also be some buffer/array
        static BOOL fn_800E4A04(u32);

        /* 0x0C */ virtual BOOL vt_0C(ToolDataRef*); // Something with ItemInfo/OpenDoorNo, could be spawning an enemy?
        /* 0x10 */ virtual BOOL vt_10(ToolDataRef*); // My guess is the opposite, despawning?
        /* 0x14 */ virtual BOOL vt_14(ToolDataRef*, char*); // Something with Luigi name and setting enemy strategy state?

        void fn_800E52BC(ToolData*);
        u32 findLuigiAppearIndex(ToolData*, u32);
        ToolDataRef* fn_800E5488(s32);
        
        Vec* fn_800E5564(s32);
        u32 fn_800E55AC(s32);
        s32 fn_800E55F0(s32); // Gets _0 member from AppearSlot
        void* fn_800E5600(s32); // Dynamicaly casts Player to MoveObj 
        void* fn_800E5634(s32); // Helper function to get a player object from fn_80069130 (by taking in _E08[param_1]._0?)

        s32 fn_800E5660(JGeometry::TVec3f*, JGeometry::TVec3f*, f32);
        s32 fn_800E56E4(JGeometry::TVec3f*, JGeometry::TVec3f*);
        s32 fn_800E5784(JGeometry::TVec3f*, JGeometry::TVec3f*);

        s32 fn_800E5868(s32, s32);
        unkEnManager1* fn_800E58D4(u32, ToolData*, s32); // Needs more decompilation
        void fn_800E59D4(s32);
        static void fn_800E5A00(unkEnManager1Wrapper*, EnManager*); // TODO Fake Match, probably not static
        EnThought* fn_800E5A14(s32);
        EnThought* fn_800E5A80(s32); // Requires some lbl to be decompiled: lbl_803D7004
        void fn_800E5ABC(s32);
        void fn_800E5AE8(); // Requires some lbl to be decompiled: lbl_80363BF8
        BOOL fn_800E5B88(); // Requires that fn_800AD39C and its resulting struct/class be decompiled more.
        s32 fn_800E5BF8(const char*); // I think this depends on MoveObj, which probably need more details from here.
        s32 fn_800E5D18(const char*); // Requires some lbl to be decompiled: lbl_80363B88
        static int fn_800E5E60(int);  // Requires some lbl to be decompiled: lbl_80363B50
        void fn_800E5E78(const char*);

    public:
        /* 0x004 */ MR::FixedArray<unkEnManager1, 0x80> _4;
        /* 0x804 */ MR::AssignableArray<unkEnManager2, 0x80> _804; // Explicitly not ArrayHolder
        /* 0xE08 */ AppearPointSlot _E08[2];
        /* 0xE40 */ Koga::ToolData* mInfoTable;
        /* 0xE44 */ u8 _E44;
    };
};

// Maybe apart of AppearPointSlot? Looks like compiler generated but unsure
void fn_800E61C0();

#endif
