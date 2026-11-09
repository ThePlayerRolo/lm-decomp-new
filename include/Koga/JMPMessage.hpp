#ifndef JMP_MESSAGE_H_
#define JMP_MESSAGE_H_

#include <JSystem/JORReflexible.hpp>
#include "Koga/Message.hpp"
#include "MR/Array.hpp"

namespace Koga {
    class ToolData;
}

class unkJmpMessageSender1 {
public:
    unkJmpMessageSender1();

    /* 0x0 */ s32 _0;
    /* 0x4 */ u8 _4[0xC];
};

class JmpMessageSender : public MessageSender, public JORReflexible {
public:

    JmpMessageSender();

    /* 0x08 */ virtual ~JmpMessageSender();
    /* 0x0C */ virtual void vt_0C();
    /* 0x10 */ virtual void vt_10();

    BOOL add(Koga::ToolData* pData);
    BOOL remove(Koga::ToolData* pData);

    void fn_800EB634(Koga::ToolData*, s32, bool);
    BOOL fn_800EAA00(const char*, s32);
    void fn_800EAB1C();

    // Something with checking events, specifically pos, appear/disappear flags, and event set no;
    static void fn_800EAC0C(Koga::ToolData*, void*); // Unsure of return / if static or arg 2
    static void fn_800EAF00(u8*); // Looks to reset a bunch of bool flags? Unsure of return / if static

    void fn_800EB1DC();
    void fn_800EB27C();
    void fn_800EB528();
    void fn_800EB5CC(u8*);
    void fn_800EB564(u8*);

public:
    /* 0x038 */ MR::AssignableArray<unkJmpMessageSender1, 200> _38;
    /* 0xCBC */ MR::ArrayHolder<Koga::ToolData*, 10> _CBC;
    /* 0xCE8 */ u8 _CE8;
    /* 0xCE8 */ u8 _CE9[262];
};

#endif
