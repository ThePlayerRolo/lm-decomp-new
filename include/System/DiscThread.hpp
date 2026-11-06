#ifndef DISC_THREAD_HPP
#define DISC_THREAD_HPP

#include <dolphin/os/OSMessage.h>
#include <types.h>

#define MAX_DISC_FILE_INFO_ARR 64

struct DiscFileInfo;

void initDiscThread();
void sendDiscRequest(DiscFileInfo*);

struct DiscThread : public OSThread {
    /* 0x310 */ OSMessageQueue mMsgQueue;
    /* 0x330 */ OSMessage mMsgs[MAX_DISC_FILE_INFO_ARR];
    /* 0x430 */ DiscFileInfo* mCurrFileInfo;
};

#endif
