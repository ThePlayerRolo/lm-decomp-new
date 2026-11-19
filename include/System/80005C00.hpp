#ifndef _80005C00_HPP
#define _80005C00_HPP

#include <dolphin/os/OSMessage.h>
#include <dolphin/os/OSThread.h>
#include <types.h>

void fn_80005C00();
void fn_80005E04();

struct UnkThread {
    /* 0x000 */ OSThread mThread;
    /* 0x310 */ OSMessageQueue mMsgQueue;
    /* 0x330 */ OSMessage mMsg;
};

extern UnkThread lbl_8039A900;
extern s32 lbl_804D7FF0;

#endif
