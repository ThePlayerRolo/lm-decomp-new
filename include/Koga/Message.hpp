#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <types.h>

#include "MR/Array.hpp"

class ToolDataRef;

class MessageReceiver;
typedef bool (MessageReceiver::*MessageCallback1)(int arg0);
typedef bool (MessageReceiver::*MessageCallback2)(int arg0, int arg1);

class MessageSender {
public:
    MessageSender();

    /* 0x08 */ virtual ~MessageSender();
    /* 0x0C */ virtual void vt_0C() = 0;
    /* 0x10 */ virtual void vt_10() = 0;
    /* 0x14 */ virtual s32 vt_14(MessageCallback1 fn, int arg0);
    /* 0x18 */ virtual s32 vt_18(MessageCallback2 fn, int arg0, int arg1);

    bool addReceiver(MessageReceiver*);

public:
    /* 0x4 */ MR::ArrayHolder<MessageReceiver*, 12> _4;
};

class IMessageReceiver {
public:
    //Seems to be inlined where its used and doesn't show up in the final binary
    /* 0x08 */ inline virtual ~IMessageReceiver() { }
    /* 0x0C */ virtual BOOL vt_0C(ToolDataRef*) = 0;
    /* 0x10 */ virtual BOOL vt_10(ToolDataRef*) = 0;
    /* 0x14 */ virtual BOOL vt_14(ToolDataRef*, char*) = 0;
};

class MessageReceiver : public IMessageReceiver {
public:
    MessageReceiver();

    /* 0x08 */ virtual ~MessageReceiver();
    /* 0x0C */ virtual BOOL vt_0C(ToolDataRef*);
    /* 0x10 */ virtual BOOL vt_10(ToolDataRef*);
    /* 0x14 */ virtual BOOL vt_14(ToolDataRef*, char*);
};

#endif
