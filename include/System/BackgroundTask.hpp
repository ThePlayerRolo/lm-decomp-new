#ifndef BACKGROUND_TASK_HPP
#define BACKGROUND_TASK_HPP

#include <dolphin/os/OSMessage.h>
#include <types.h>

typedef void (*BackgroundTaskFunc)();
struct BackgroundTask : public OSThread {
    /* 0x310 */ OSMessageQueue mMsgSendQueue;
    /* 0x330 */ OSMessage mSendMsg;
    /* 0x334 */ OSMessageQueue mMsgRecvQueue;
    /* 0x354 */ OSMessage mRecvMsg;
    /* 0x358 */ BackgroundTaskFunc mCallback;
};

void initBackgroundTask();
void startBackgroundTask(BackgroundTaskFunc);
s32 pollBackgroundTaskComplete();

#endif
