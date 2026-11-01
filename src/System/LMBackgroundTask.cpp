#include "System/LMBackgroundTask.hpp"
#include <dolphin/os.h>
#include <dolphin/os/OSFastCast.h>

struct BackgroundTask : public OSThread {
    static u8 sBackgroundTaskStack[0x4000];
    static BackgroundTask sBackgroundTask;

    /* 0x310 */ OSMessageQueue mMsgSendQueue;
    /* 0x330 */ s32 _330;
    /* 0x334 */ OSMessageQueue mMsgRecvQueue;
    /* 0x354 */ s32 _354;
    /* 0x358 */ LMBackgroundTaskCallback mCallback;
};

u8 BackgroundTask::sBackgroundTaskStack[0x4000];
BackgroundTask BackgroundTask::sBackgroundTask;

namespace LMBackgroundTask {    
    void init() {
        initBackgroundTaskInternal(&BackgroundTask::sBackgroundTask);
    }

    void start(LMBackgroundTaskCallback cb) {
        BackgroundTask::sBackgroundTask.mCallback = cb;
        OSReceiveMessage(&BackgroundTask::sBackgroundTask.mMsgRecvQueue, nullptr, OS_MESSAGE_NOBLOCK);
        OSSendMessage(&BackgroundTask::sBackgroundTask.mMsgSendQueue, nullptr, OS_MESSAGE_NOBLOCK);
    }

    s32 pollDone() {
        return OSReceiveMessage(&BackgroundTask::sBackgroundTask.mMsgRecvQueue, nullptr, OS_MESSAGE_NOBLOCK);
    }

    void* createThreadCallback(void*) {
        OSInitFastCast();

        while (true) {
            OSReceiveMessage(&BackgroundTask::sBackgroundTask.mMsgSendQueue, nullptr, OS_MESSAGE_BLOCK);

            if (BackgroundTask::sBackgroundTask.mCallback != nullptr) {
                BackgroundTask::sBackgroundTask.mCallback();
            }

            OSSendMessage(&BackgroundTask::sBackgroundTask.mMsgRecvQueue, nullptr, OS_MESSAGE_NOBLOCK);
        }
    }

    void initBackgroundTaskInternal(BackgroundTask* thread) {
        OSInitMessageQueue(&thread->mMsgSendQueue, &thread->_330, 1);
        OSInitMessageQueue(&thread->mMsgRecvQueue, &thread->_354, 1);
        u32 size = sizeof(BackgroundTask::sBackgroundTaskStack);
        OSCreateThread(thread, createThreadCallback, nullptr, &BackgroundTask::sBackgroundTaskStack[size], size, 17, OS_THREAD_ATTR_DETACH);
        OSResumeThread(thread);
    }
}
