#include <JSystem/JKernel/JKRArchive.hpp>
#include <dolphin/os/OSFastCast.h>

#include "System/LMDvdThread.hpp"
#include "Unsorted/80005EB8.hpp"
#include "System/LMDvdFile.hpp"

struct LMDvdThread : public OSThread {
    /* 0x310 */ OSMessageQueue _310;
    /* 0x330 */ void* _330[64];
    /* 0x430 */ LMDvdFileInfo* mFileInfoArray;
};

static u8 sDvdThreadStack[0x2000];
static LMDvdThread sDvdThread;

namespace LMDvdThreading {
    void init() {
        initDvdThread(&sDvdThread);
    }

    void sendDvdRequest(LMDvdFileInfo* pInfo) {
        OSSendMessage(&sDvdThread._310, pInfo, OS_MESSAGE_BLOCK);
    }

    static void* createDvdThreadCallback(void* pPtr) {
        OSInitFastCast();

        while (true) {
            void* msg;
            OSReceiveMessage(&sDvdThread._310, &msg, OS_MESSAGE_BLOCK);

            LMDvdFileInfo* info = (LMDvdFileInfo*)msg;

            if (info->mFileBuffer == nullptr) {
                u8 groupId = fn_800061B8(info->mHeapGroupID);

                info->mFileBuffer = reinterpret_cast<u8*>(LMDvdFile::alloc(info->mAlignedFileSize, LMDvdFile::getAllocDirection() * 32));

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
                LMDvdFile::closeFile(nullptr, info);
                u8 groupId = fn_800061B8(info->mHeapGroupID);
                if (info->mPostLoadFunc != nullptr) {
                    info->mPostLoadFunc(info->mFileBuffer, info);
                }

                if (sFileDataError == 0) {
                    if (info->mCallback != nullptr) {
                        info->mCallback(nullptr, info);
                    }

                    fn_800061B8(groupId);

                    sDvdThread.mFileInfoArray = sDvdThread.mFileInfoArray->_7C;
                }
                break;
            }
        }
    }

    void initDvdThread(LMDvdThread* thread) {
        OSInitMessageQueue(&thread->_310, thread->_330, ARRAY_COUNT(thread->_330));
        thread->mFileInfoArray = LMDvdFile::getFileInfoRing();
        u32 size = sizeof(sDvdThreadStack);
        OSCreateThread(thread, createDvdThreadCallback, nullptr, &sDvdThreadStack[size], size, 10, OS_THREAD_ATTR_DETACH);
        OSResumeThread(thread);
    }
}
