#include <dolphin/os/OSFastCast.h>

#include "System/BackgroundTask.hpp"

static void* createBackgroundTaskThreadCallback(void*);
static void initBackgroundTaskInternal(BackgroundTask*);

static u8 sBackgroundTaskStack[0x4000] ATTRIBUTE_ALIGN(32);
static BackgroundTask sBackgroundTask;

void initBackgroundTask() {
    initBackgroundTaskInternal(&sBackgroundTask);
}

void startBackgroundTask(BackgroundTaskFunc pCallback) {
    sBackgroundTask.mCallback = pCallback;
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

void initBackgroundTaskInternal(BackgroundTask* pTask) {
    OSInitMessageQueue(&pTask->mMsgSendQueue, &pTask->mSendMsg, 1);
    OSInitMessageQueue(&pTask->mMsgRecvQueue, &pTask->mRecvMsg, 1);
    u32 size = sizeof(sBackgroundTaskStack);
    OSCreateThread(pTask, createBackgroundTaskThreadCallback, nullptr, &sBackgroundTaskStack[size], size, 17, OS_THREAD_ATTR_DETACH);
    OSResumeThread(pTask);
}
