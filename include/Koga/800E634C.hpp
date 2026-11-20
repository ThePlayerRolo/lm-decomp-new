#ifndef KOGA_800E634C_HPP
#define KOGA_800E634C_HPP

#include <types.h>
#include <JSystem/JGeometry/JGVec3.hpp>

namespace Koga {
    class ToolData;
}

class EnThought;
class MoveObj;

struct SomeStruct {
    u16 _0;  // Dir X? Needs validation
    u16 _2;  // Dir Y? Needs validation
    u16 _4;  // Dir Z? Needs validation
    JGeometry::TVec3f _C;
};

// Some TVec3f Helpers? Not sure about args/returns, but would make sense the template class would copy over some of the functions to a class where used.
void fn_800E634C();
void fn_800E63AC(JGeometry::TVec3f*, EnThought*, u16, f32, f32, f32);
void fn_800E655C();
BOOL fn_800E65C8(JGeometry::TVec3f*, EnThought*, u16, f32, f32);
BOOL fn_800E6648(JGeometry::TVec3f*, EnThought*, JGeometry::TVec3f*, f32, f32, f32);
void fn_800E66FC();
BOOL fn_800E6764(JGeometry::TVec3f*, EnThought*, f32, f32, f32);
s32 fn_800E689C(JGeometry::TVec3f*, Koga::ToolData*, s32); // Could be ToolDataRef?
void fn_800E6948(JGeometry::TVec3f*, Koga::ToolData*);
void fn_800E6A3C(JGeometry::TVec3f*, Koga::ToolData*, s32); // Could be ToolDataRef?
void fn_800E6AB8(JGeometry::TVec3f*, Koga::ToolData*, f32);

void fn_800E6C5C();
void fn_800E6D24();
void fn_800E6DE4();
bool fn_800E6ED0(EnThought*);
void fn_800E6FCC();

// All of these are miscelaneous functions I havent touched/reviewed. Feel free to move, re-organize, etc.
bool fn_800E7054();
s32 fn_800E70BC();
void fn_800E7114();
bool fn_800E7174(JGeometry::TVec3f*, s32);
bool fn_800E71D4(JGeometry::TVec3f*, s32);
bool fn_800E7280(s32);
void fn_800E730C();
void fn_800E7378();
void* fn_800E7510(void*, void*);
void fn_800E75B8(JGeometry::TVec3f*, void*);
void fn_800E760C(void*);
void fn_800E7628(void*);
BOOL fn_800E7634(Koga::ToolData*);
bool fn_800E7650(void*);
bool fn_800E7698(s32, void**, void**);
void fn_800E7ED8(void*, void*);

// Could be another sub-class? Unsure
void* fn_800E7FC0(void*);
void* fn_800E7FF8(void*, s16);
void fn_800E805C(void*, void*);
void fn_800E8098(void*);

// All of these are miscelaneous functions I havent touched/reviewed in depth. Feel free to move, re-organize, etc.
void fn_800E8180();
s32 fn_800E82AC(f32);


#endif
