#include <JSystem/JGeometry/JGVec3.hpp>

#include "Koga/MapCol.hpp"
#include "Koga/ToolData.hpp"
#include "Sato/EnThought.hpp"
#include "Koga/800E634C.hpp"
#include "Unsorted/MoveObj.hpp"

f32 fn_800E6C5C(EnThought* pThought) {
    JGeometry::TVec3f& charPosition = pThought->getCharacter()->_44;
    ToolDataRef dataRef = pThought->getToolDataRef();

    if (dataRef.isValid()) {
        u32 floatingHeight = 0;
        dataRef.getToolData()->getValue(dataRef.mEntryIndex, "floating_height", &floatingHeight);
        return floatingHeight;
    }

    f32 val_1 =  Koga::MapCol::sCurMapCol->fn_800BBE08(charPosition);
    f32 val_2  = Koga::MapCol::sCurMapCol->fn_800BBE2C(charPosition);

    return (val_2 - val_1) * 0.5f;
}

bool fn_800E6ED0(EnThought* pThought) {
    if (!pThought->getToolDataRef().isValid()) {
        return false;
    }

    SomeStruct temp;
    temp._0 = 0;
    temp._2 = 0;
    temp._4 = 0;
    pThought->getPosition(&temp._C);
    pThought->getDirectionNormalized(&temp._0, &temp._2, &temp._4);

    JGeometry::TVec3f vec(temp._C);

    pThought->getCharacter()->fn_80067CB0(vec.x, vec.y, vec.z);
    pThought->getCharacter()->vt_0C(temp._0, temp._2, temp._4);

    return true;
}
