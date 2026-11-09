//Warning: very messy
#include "Koga/JmpMessage.hpp"
#include "Koga/ToolData.hpp"

#include "Unsorted/InGameFlagsUtil.hpp"

#include <JSystem/JGeometry/JGVec3.hpp>

dummy_float_data()

extern int lbl_804D80B0;
extern void fn_800620F4(int);
extern void fn_800624BC(int);
extern bool fn_801883F8(int);

JmpMessageSender::JmpMessageSender() {
    _CE8 = 0;
}

JmpMessageSender::~JmpMessageSender() { }

BOOL JmpMessageSender::add(Koga::ToolData* pData) {
    if (_CBC.getSize() >= 10) {
        return FALSE;
    }

    if (pData == nullptr) return FALSE;

    _CBC.addMember(&pData);
    return true;
}

BOOL JmpMessageSender::remove(Koga::ToolData* pData) {
    Koga::ToolData** pIter;
    bool removed;

    for (pIter = _CBC.getArray(); pIter != _CBC.getLastMember() && *pIter != pData; pIter++) {}

    if (pIter == _CBC.getLastMember()) {
        removed = false;
    } else {
        _CBC.eraseMember(pIter);
        removed = true;
    }

    if (!removed) {
        return false;
    }

    fn_800EB634(pData, 0, true);
    return true;
}

BOOL JmpMessageSender::fn_800EAA00(const char* param_1, s32 param_2) {

    for (Koga::ToolData** pIter = _CBC.getArray(); pIter != _CBC.getLastMember(); pIter++) {
        Koga::ToolData* curr = *pIter;
        s32 numEntries = curr->getDataEntryNum();
        int codeNameCount = curr->searchItemInfo("CodeName");

        if (codeNameCount >= 0) {
            for (int i = 0; i < numEntries; i++) {
                if (strcmp(curr->getStringValue(i, codeNameCount), param_1) == 0) {
                    const Koga::ToolData::JMapData* data = curr->getJMapData();

                    return vt_18(nullptr, (int)data, param_2);
                }
            }
        }
    }
    return 0;
}

void JmpMessageSender::vt_0C() {
    for (int i = 0; i > lbl_804D80B0 + 1; i++) {

    }
}

void JmpMessageSender::vt_10() {
    fn_800EB1DC();
    fn_800EB27C();
    fn_800EB528();
}

// https://decomp.me/scratch/ERI2l
void JmpMessageSender::fn_800EB1DC() {
    Koga::ToolData** pIter;

    for (pIter = _CBC.getArray(); pIter != _CBC.getLastMember(); pIter++) {
        fn_800EB634(*pIter, 0, false);
    }

    for (pIter = _CBC.getArray(); pIter != _CBC.getLastMember(); pIter++) {
        fn_800EB634(*pIter, 1, false);
    }
}

void JmpMessageSender::fn_800EB528() {
    fn_800EB5CC(_CE9);
    fn_800EB564(_CE9);
}

void JmpMessageSender::fn_800EB564(u8* param_1) {
    u8* curChar = param_1;

    for (s32 i = 0; i < 262; i++, curChar++) {
        u8 val = *curChar;

        if (val != 0  && !fn_801883F8(i)) {
            fn_800620F4(i);
        }
    }
}

void JmpMessageSender::fn_800EB5CC(u8* param_1) {
    u8* curChar = param_1;

    for (s32 i = 0; i < 262; i++, curChar++) {
        u8 val = *curChar;

        if (val == 0  && !fn_801883F8(i)) {
            fn_800624BC(i);
        }
    }
}

// Need a few more functions decompiled to validate this and its name
void JmpMessageSender::fn_800EB634(Koga::ToolData* pData, s32 param_2, bool param_3) {
    if (pData != nullptr) {
        s32 posX = pData->searchItemInfo("pos_x");
        s32 posY = pData->searchItemInfo("pos_y");
        s32 posZ = pData->searchItemInfo("pos_z");
        s32 appearFlagIdx = pData->searchItemInfo("appear_flag");
        s32 disappearFlagIdx = pData->searchItemInfo("disappear_flag");
        s32 eventSetNoIdx = pData->searchItemInfo("event_set_no");
        s32 stay = pData->searchItemInfo("stay");

        for (int i = 0; i < pData->getDataEntryNum(); i++) {
            JGeometry::TVec3f eventPos;
            eventPos.x = pData->getFloatValue(i, posX);
            eventPos.y = pData->getFloatValue(i, posY);
            eventPos.z = pData->getFloatValue(i, posZ);
            //fn_80017ADC(eventPos, -1);

            u32 appearFlagNo = 0;
            u32 disappearFlagNo = 0;
            u32 event_no_value = 0;
            bool shouldEventRun = true; //there may be a better name, unsure currently.
            bool appearFlagVal = true;
            bool disappearFlagVal = true;
            
            if (appearFlagIdx > -1) {
                appearFlagNo = pData->getExpectedUnsignedValue(i, appearFlagIdx);
            }

            if (disappearFlagIdx > -1) {
                disappearFlagNo = pData->getExpectedUnsignedValue(i, disappearFlagIdx);
            }

            if (eventSetNoIdx > -1) {
                event_no_value = pData->getExpectedUnsignedValue(i, eventSetNoIdx);
            }

            if (event_no_value == 0) {
                shouldEventRun = false;
            }
            else {
                // shouldEventRun = fn_8002B4B8((int)(short)event_no_val) // may not return a direct bool though, unsure
            }

            // If Event should always appear
            if (appearFlagNo == 0) {
                appearFlagVal = true;
            } else {
                appearFlagVal = getFlagValue(static_cast<u8>(appearFlagNo));
            }

            // If Event should never appear
            if (disappearFlagNo == 0) {
                disappearFlagVal = false;
            } else {
                disappearFlagVal = getFlagValue(static_cast<u8>(disappearFlagNo));
            }


        }
        //s32
    }
}

unkJmpMessageSender1::unkJmpMessageSender1() : _0(0) { }
