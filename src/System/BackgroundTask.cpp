#include <dolphin/os.h>
#include <dolphin/os/OSFastCast.h>

#include "System/BackgroundTask.hpp"
#include "dolphin/os/OSMessage.h"

struct BackgroundTask : public OSThread {
    /* 0x310 */ OSMessageQueue mMsgSendQueue;
    /* 0x330 */ OSMessage mSendMsg;
    /* 0x334 */ OSMessageQueue mMsgRecvQueue;
    /* 0x354 */ OSMessage mRecvMsg;
    /* 0x358 */ BackgroundTaskFunc mCallback;
};

static u8 sBackgroundTaskStack[0x4000] ATTRIBUTE_ALIGN(32);
static BackgroundTask sBackgroundTask;

void initBackgroundTask() {
    initBackgroundTaskInternal(&sBackgroundTask);
}

void startBackgroundTask(BackgroundTaskFunc cb) {
    sBackgroundTask.mCallback = cb;
    OSReceiveMessage(&sBackgroundTask.mMsgRecvQueue, nullptr, OS_MESSAGE_NOBLOCK);
    OSSendMessage(&sBackgroundTask.mMsgSendQueue, nullptr, OS_MESSAGE_NOBLOCK);
}

s32 pollBackgroundTaskComplete() {
    return OSReceiveMessage(&sBackgroundTask.mMsgRecvQueue, nullptr, OS_MESSAGE_NOBLOCK);
}

void* createBackgroundTaskThreadCallback(void*) {
    OSInitFastCast();

    while (true) {
        OSReceiveMessage(&sBackgroundTask.mMsgSendQueue, nullptr, OS_MESSAGE_BLOCK);

        if (sBackgroundTask.mCallback != nullptr) {
            sBackgroundTask.mCallback();
        }

        OSSendMessage(&sBackgroundTask.mMsgRecvQueue, nullptr, OS_MESSAGE_NOBLOCK);
    }
}

void initBackgroundTaskInternal(BackgroundTask* thread) {
    OSInitMessageQueue(&thread->mMsgSendQueue, &thread->mSendMsg, 1);
    OSInitMessageQueue(&thread->mMsgRecvQueue, &thread->mRecvMsg, 1);
    u32 size = sizeof(sBackgroundTaskStack);
    OSCreateThread(thread, createBackgroundTaskThreadCallback, nullptr, &sBackgroundTaskStack[size], size, 17, OS_THREAD_ATTR_DETACH);
    OSResumeThread(thread);
}
