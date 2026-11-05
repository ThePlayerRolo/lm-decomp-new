#include <JSystem/JKernel/JKRArchive.hpp>
#include <dolphin/os/OSFastCast.h>
#include <dolphin/os/OSMessage.h>

#include "System/DiscThread.hpp"
#include "Unsorted/80005EB8.hpp"
#include "System/DiscFile.hpp"

struct DiscThread : public OSThread {
    /* 0x310 */ OSMessageQueue mMsgQueue;
    /* 0x330 */ OSMessage mMsgs[MAX_FILE_INFO_ARR];
    /* 0x430 */ DiscFileInfo* mCurrFileInfo;
};

static u8 sDvdThreadStack[0x2000] ATTRIBUTE_ALIGN(32);
static DiscThread sDvdThread;

void initDiscThread() {
    initDiscThread(&sDvdThread);
}

void sendDiscRequest(DiscFileInfo* pInfo) {
    OSSendMessage(&sDvdThread.mMsgQueue, pInfo, OS_MESSAGE_BLOCK);
}

void* createDiscThreadCallback(void* pPtr) {
    OSInitFastCast();

    while (true) {
        void* msg;
        OSReceiveMessage(&sDvdThread.mMsgQueue, &msg, OS_MESSAGE_BLOCK);

        DiscFileInfo* info = (DiscFileInfo*)msg;

        if (info->mFileBuffer == nullptr) {
            u8 groupId = fn_800061B8(info->mHeapGroupID);

            info->mFileBuffer = reinterpret_cast<u8*>(allocDiscFile(info->mAlignedFileSize, getDiscFileAllocDirection() * 32));

            //Have no idea what was meant to be for since the block of code for it is optimized out sooooooo
            if (info->mFileBuffer == nullptr) { info = info; }

            fn_800061B8(groupId);
            info->mBufferBreakFlag = MBF_1;
        }

        s32 readResult = DVDReadPrio(info, info->mFileBuffer, info->mAlignedFileSize, 0, 2);
        switch (readResult) {
            case DVD_RESULT_FATAL_ERROR:
            case -3:
                break;
            case DVD_RESULT_IGNORED:
            default:
            closeDiscFile(nullptr, info);
            u8 groupId = fn_800061B8(info->mHeapGroupID);
            if (info->mPostLoadFunc != nullptr) {
                info->mPostLoadFunc(info->mFileBuffer, info);
            }

            if (sFileDataError == 0) {
                if (info->mCallback != nullptr) {
                    info->mCallback(nullptr, info);
                }

                fn_800061B8(groupId);

                sDvdThread.mCurrFileInfo = sDvdThread.mCurrFileInfo->mNext;
            }
            break;
        }
    }
}

void initDiscThread(DiscThread* thread) {
    OSInitMessageQueue(&thread->mMsgQueue, thread->mMsgs, ARRAY_COUNT(thread->mMsgs));
    thread->mCurrFileInfo = getDiscFileInfoRing();
    u32 size = sizeof(sDvdThreadStack);
    OSCreateThread(thread, createDiscThreadCallback, nullptr, &sDvdThreadStack[size], size, 10, OS_THREAD_ATTR_DETACH);
    OSResumeThread(thread);
}
