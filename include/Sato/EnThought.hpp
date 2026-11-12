#ifndef EN_THOUGHT_HPP
#define EN_THOUGHT_HPP

#include <JSystem/JORReflexible.hpp>
#include <JSystem/JGeometry/JGVec3.hpp>

#include "MR/Array.hpp"
#include "Koga/ToolData.hpp"
#include "Sato/EnReplace.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "Sato/IncludeStrategy.hpp"
#include "Koga/ValueControl.hpp"
#include "Unsorted/Character.hpp"

namespace Koga {
    class CharacterEvent;
    class EnManager;
}

class EnemyStrategy;

class MoveObjAlphaControl : public Koga::ValueControl<int> {
public:
    MoveObjAlphaControl();
    virtual void vt_08();

    /* 0x04 */ s32 _04;
    /* 0x08 */ s32 _08;
    /* 0x0C - 0x14 */ JGeometry::TVec3<f32> _0C; // mPosition
    /* 0x18 */ void* _18; /* seems to be an object */
};


class EnThought0x14 {
    /* 0x00 */ void* unk_0; /* an object */
    /* 0x04 */ void* unk_4; /* a number */
    /* 0x08 */ f32 unk_8[3]; // Possibly the TVec3F said below 

    // These are called via Array::callAll fn_800C17EC most likely, and functors rather than virtuals.
    void vt_28_ptmf(); // fn_800BEF3C
    void vt_3c_ptmf(); // fn_800BEEDC
    void vt_40_ptmf(); // fn_800BEF0C
};

/**
 * 0x0 - IncludeStrategy
 * 0x808 - JORReflexible
 */
class EnThought : public IncludeStrategy, public JORReflexible  {
public:
    EnThought();
    virtual ~EnThought();
    virtual void vt_0C() = 0; // Did not check args/return type
    virtual void vt_10() { }; // Did not check args/return type

    void fn_800BF384(); // Did not check return type
    void fn_800BF3E0(); // Did not check return type
    void fn_800BF81C(); // Did not check args/return type. So many function calls.
    void fn_800BFB98(const char*, s32);
    void reset(); //  fn_800BF0CC lmao golden function
    void setToolDataRef(Koga::ToolData*, s32);
    ToolDataRef getToolDataRef() const;

    bool getPosition(JGeometry::TVec3f*);
    bool getDirectionNormalized(u16*, u16*, u16*);

    s32 fn_800C0E48(f32);
    static bool fn_800C0F08(EnemyStrategy*, Koga::CharacterEvent*);

    void fn_800C17EC();

    void fn_800C19CC(s32);
    bool fn_800C15E0(s32); // Unsure about return type/args

    void fn_800C1B84();
    void fn_800C1B88();
    EnemyStrategy* fn_800C1B8C();

    void fn_800C1B9C();
    void fn_800C1BA0(); // Sets the EnemyStrategy to nullptr?

    inline MoveObjAlphaControl getAlphaControl() { return mAlphaControl; }
    inline void set810(void* vVal) { _810 = vVal; }

    inline Character* getCharacter() const { return _808; }
    inline bool isValid() const { 
        return mpToolData != nullptr && 
        mEntryIdx >= 0; 
    }

    // Object that holds at least 0xE8 data. In the reset, it's calling fn_80067C30 which is in MoveObj split. Probably an entity
    /* 0x808 */ Character* _808; 
    /* 0x80C */ Koga::EnManager* _80C;
    /* 0x810 */ void* _810;
    /* 0x814 */ void* _814;
    /* 0x818 */ void* _818;
    /* 0x81c */ void* _81c;
    /* 0x820 */ void* _820;
    /* 0x824 */ void* _824;
    /* 0x828 - 0x890 */ MR::AssignableArray<EnThought0x14, 5> array_828; // 0x14 * 5 + arraysize at 0x88c
    /* 0x890 */ s32 _890;
    /* 0x894 */ void* _894;
    /* 0x898 */ void* _898;
    /* 0x89c */ void* _89c;
    /* 0x8a0 */ void* _8a0;
    /* 0x8a4 */ MoveObjAlphaControl mAlphaControl;
    /* 0x8c0 */ Koga::ToolData* mpToolData;
    /* 0x8c4 */ s32 mEntryIdx;
    /* 0x8c8 */ s32 _8c8;
    /* 0x8cc */ void* _8cc;
    /* 0x8d0 */ u8 _8d0; //Unsure of type
    /* 0x8d1 - 0x8d3 */ u8 _8d1[3]; //Probably padding
    /* 0x8d4 */ void* _8d4[0x4]; //Unsure about size or anything here, just matching the gap.
    /* 0x8e4 */ float _8e4;
    /* 0x8e8 */ u16 _8e8; // Unsure of type
    /* 0x8EA */ u8 _8EA; // Unsure of type
    /* 0x8EB */ u8 _8EB; // Probably padding
    /* 0x8ec */ EnReplace m8ec;
    /* 0x900 */ void* _900;
    /* 0x904 */ u8 _904;
    /* 0x905 */ u8 _905;
    /* 0x906 */ u8 _906;
    /* 0x906 */ u8 _907; // Probably padding
    /* 0x908 */ void* _908;
    /* 0x90c */ void* _90c;
    /* 0x910 */ void* _910;
    /* 0x914 */ void* _914;
    /* 0x918 */ void* _918;
    /* 0x91c */ u8 _91c;
    /* 0x91d */ u8 _91d[3]; // Probably Padding
    /* 0x920 */ void* _920;
    /* 0x924 */ u8 _924;
    /* 0x925 */ u8 _925[3]; // Probably Padding
    /* 0x928 */ void* _928;
    /* 0x92c */ void* _92c;
    /* 0x930 */ void* _930;
    /* 0x934 */ void* _934;
    /* 0x938 */ void* _938;
};

#endif
