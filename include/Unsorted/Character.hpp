#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Unsorted/MoveObj.hpp"
#include <JSystem/JGeometry/JGVec3.hpp>

// The split is not right. (lower bound and upper bound are just vrom vtable for now)
class Character : public MoveObj {
public:
    Character();

    /* 0x08 */ virtual ~Character();
    /* 0x0c */ virtual void vt_0c();
    /* 0x10 */ virtual void vt_10();
    /* 0x14 */ virtual void vt_14();
    /* 0x18 */ virtual s32 vt_18();
    /* 0x1C */ virtual void vt_1C(JGeometry::TVec3f*);
    /* 0x20 */ virtual void vt_20(void*); // Unsure of arg type.

public:
    /* 0x78C */ s32 _78C;

    static u16 fn_8006A3BC(s32, u16);
};

// All of these are referenced in EnManager. No arg types or return types are guaranteed.
s32 characterInit(void*, void*);
Character* fn_80069130(s32 idx);

#endif
