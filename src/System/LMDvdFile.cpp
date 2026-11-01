#include "System/LMDvdFile.hpp"
#include "System/Yay0.hpp"
#include "System/LMDvdThread.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "Unsorted/GamePad.hpp"
#include "Unsorted/80005EB8.hpp"
#include "types.h"

struct LMDvdFileQueue {
    void updateDvdDriveStatus();
    void getNextSlot();
    bool openFile(const char*, u8*);
    void* openFileAsync(const char*, LMDvdFileInfoCallback, u8*, void*);
  
    static LMDvdFileInfo sFileInfoRing[MAX_FILE_INFO_ARR];
    static LMDvdFileQueue sCurDvdFile;
    
    /* 0x00 */ s32 _0;
    /* 0x04 */ AllocDirection mAllocDirection;
    /* 0x08 */ LMDvdFileInfo* mCurrFileInfo;
    /* 0x10 */ u8 _10[0x2C - 0x10];
};

LMDvdFileInfo LMDvdFileQueue::sFileInfoRing[MAX_FILE_INFO_ARR];
LMDvdFileQueue LMDvdFileQueue::sCurDvdFile;
s32 sFileDataError;

namespace LMDvdFile {
    void* alloc(u32 size, s32 align) {
        return fn_80006080(size, align);
    }

    LMDvdFileInfo* getFileInfoRing() {
        return &LMDvdFileQueue::sFileInfoRing[0];
    }
}

void LMDvdFileQueue::updateDvdDriveStatus() {
    s32 driveStatus = DVDGetDriveStatus();

    if (sFileDataError != 0) {
        driveStatus = DVD_STATE_FATAL_ERROR;
    }

    switch (driveStatus) {
    case DVD_STATE_FATAL_ERROR:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_END:
        lbl_804D80AC = 0;
        break;
    case DVD_STATE_BUSY:
        if (DVDCheckDisk() != 0) {
            lbl_804D80AC = 0;
        } else {
            driveStatus = DVD_STATE_COVER_CLOSED;
            sGamePad->stopMotor();
            lbl_804D80AC = 1;
        }
        break;
    case DVD_STATE_COVER_CLOSED:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_NO_DISK:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_COVER_OPEN:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_WRONG_DISK:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_RETRY:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    }
    fn_800473F8(driveStatus);
}

void LMDvdFileQueue::getNextSlot() {
    // TODO Remove this
    FORCE_DONT_INLINE
    LMDvdFileInfo* info = mCurrFileInfo->_7C;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    mCurrFileInfo = info;
    mCurrFileInfo->mFileBuffer = nullptr;
    mCurrFileInfo->mDecompBuffer = nullptr;
    mCurrFileInfo->mArchive = nullptr;
    mCurrFileInfo->mPostLoadFunc = nullptr;
    mCurrFileInfo->mCallback = nullptr;
    mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();
    OSReceiveMessage(&mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);
}

bool LMDvdFileQueue::openFile(const char* pFileName, u8* pBuffer) {
    // TODO Remove this
    FORCE_DONT_INLINE
    LMDvdFileInfo* info = mCurrFileInfo;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }

    DVDOpen(const_cast<char*>(pFileName), info);

    mCurrFileInfo->mAlignedFileSize = ALIGN_NEXT(info->length, 32);
    mCurrFileInfo->mBufferBreakFlag = MBF_0;
    mCurrFileInfo->mFileBuffer = pBuffer;

    LMDvdThreading::sendDvdRequest(mCurrFileInfo);
    return true;
}

// https://decomp.me/scratch/Ro97O
void* LMDvdFileQueue::openFileAsync(const char* pFileName, LMDvdFileInfoCallback pCallback, u8* pBuffer, void* pCallbackArg) {
    // TODO Remove this
    FORCE_DONT_INLINE
    mCurrFileInfo->mCallback = pCallback;
    mCurrFileInfo->mCallbackArg = pCallbackArg;

    LMDvdFileInfo* info = mCurrFileInfo;

    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }

    DVDOpen(const_cast<char*>(pFileName), info);
    mCurrFileInfo->mAlignedFileSize = ALIGN_NEXT(info->length, 32);
    mCurrFileInfo->mBufferBreakFlag = MBF_0;
    mCurrFileInfo->mFileBuffer = pBuffer;

    LMDvdThreading::sendDvdRequest(mCurrFileInfo);
    _0++;

    return mCurrFileInfo->mFileBuffer;
}

namespace LMDvdFile {
    void init() {
        LMDvdThreading::init();

        LMDvdFileInfo* curIndex = LMDvdFile::getFileInfoRing();

        LMDvdFileQueue::sCurDvdFile.mAllocDirection = ALLOC_DIR_HEAD;
        LMDvdFileQueue::sCurDvdFile._0 = 0;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo = LMDvdFile::getFileInfoRing();

        for (s32 i = 0; i < MAX_FILE_INFO_ARR; i++) {
            curIndex->_7C = &LMDvdFileQueue::sFileInfoRing[i + 1];
            OSInitMessageQueue(&curIndex->mMsgQueue, &curIndex->_5C, 1);
            curIndex++;
        }

        LMDvdFileQueue::sFileInfoRing[MAX_FILE_INFO_ARR - 1]._7C = LMDvdFile::getFileInfoRing();
    }

    u8* openFile(const char* pFileName, u8* pBuffer) {
        LMDvdFileQueue::sCurDvdFile.getNextSlot();
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallback = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallbackArg = nullptr;

        if (LMDvdFileQueue::sCurDvdFile.openFile(pFileName, pBuffer)) {
            LMDvdFileQueue::sCurDvdFile._0++;
        }

        u32 msg;

        OSReceiveMessage(&LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mMsgQueue, &msg, OS_MESSAGE_BLOCK);

        return LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mFileBuffer;
    }

    //https://decomp.me/scratch/YKS45
    u8* openFile(const char* pFileName, LMDvdFileInfoCallback pCallback, u8* pBuffer, void* pCallbackArg) {
        u8* ret;

        // Seems like inlined init, though based on LMDvdFileOpen it could not be?
        LMDvdFileInfo* info = LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->_7C;
        while (true) {
            s32 blockStatus;
            blockStatus = DVDGetCommandBlockStatus(&info->cb);
            if (blockStatus != DVD_COMMAND_READ) break;
        }
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo = info;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mFileBuffer = 0;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mDecompBuffer = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mArchive = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mPostLoadFunc = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallback = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();

        OSReceiveMessage(&LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);

        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallback = pCallback;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallbackArg = pCallbackArg;

        if (LMDvdFileQueue::sCurDvdFile.openFile(pFileName, pBuffer)) {
            LMDvdFileQueue::sCurDvdFile._0++;
            ret = LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mFileBuffer;
        }

        return ret;
    }

    //https://decomp.me/scratch/KlViD
    u8* openCompressedArchive(const char* pFileName, LMDvdFileInfoCallback pCallback, u8* pArchiveBuffer, void* pCallbackArg) {
        // Loads a Yay0-compressed archive and attempts to unpack it before mounting it.
        LMDvdFileQueue::sCurDvdFile.mAllocDirection = ALLOC_DIR_TAIL;
        // Seems like inlined init, though based on LMDvdFileOpen it could not be?
        LMDvdFileInfo* info = LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->_7C;

        while (true) {
            s32 blockStatus;
            blockStatus = DVDGetCommandBlockStatus(&info->cb);
            if (blockStatus != DVD_COMMAND_READ) break;
        }
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo = info;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mFileBuffer = 0;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mDecompBuffer = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mArchive = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mPostLoadFunc = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallback = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();

        OSReceiveMessage(&LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);

        if (pArchiveBuffer != 0) {
            LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mBufferBreakFlag = MBF_0;
        }
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mDecompBuffer = pArchiveBuffer;
        u8 oldGroupId = fn_800061B8(LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mHeapGroupID);
        void* ret = LMDvdFile::alloc(0x68, 4);
        fn_800061B8(oldGroupId);
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mArchive = reinterpret_cast<JKRMemArchive*>(ret);
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mPostLoadFunc = decompressAndMountArchive;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallback = pCallback;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallbackArg = pCallbackArg;

        if (LMDvdFileQueue::sCurDvdFile.openFile(pFileName, nullptr)) {
            LMDvdFileQueue::sCurDvdFile._0++;
        }
        LMDvdFileQueue::sCurDvdFile.mAllocDirection = ALLOC_DIR_HEAD;

        if (pArchiveBuffer != 0) {
            LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mBufferBreakFlag = MBF_0;
        }
        return reinterpret_cast<u8*>(ret);
    }

    u8* openCompressedArchive(const char* pFileName, u8* pBuffer) {
        u8* data = openCompressedArchive(pFileName, nullptr, pBuffer, nullptr);
        u32 msg;
        OSReceiveMessage(&LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mMsgQueue, &msg, OS_MESSAGE_BLOCK);
        return data;
    }

    //https://decomp.me/scratch/WwyKN
    JKRMemArchive* openMemArchive(const char* pFileName, u8* pBuffer) {
        void* buffer;
        JKRMemArchive* archive;
        u32 msg[8];

        LMDvdFileQueue::sCurDvdFile.getNextSlot();
        LMDvdFileQueue::sCurDvdFile.openFileAsync(pFileName, nullptr, pBuffer, nullptr);

        OSReceiveMessage(&LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mMsgQueue, &msg, OS_MESSAGE_BLOCK);
        buffer = LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mFileBuffer;

        archive = new JKRMemArchive();
        archive->mountFixed(buffer, MBF_1);
        return archive;
    }

    u8* openArchive(const char* pFileName, LMDvdFileInfoCallback pCallback, u8* pBuffer, void* pCallbackArg) {
        // Loads an uncompressed RARC archive and mounts it directly.
        LMDvdFileQueue::sCurDvdFile.mAllocDirection = ALLOC_DIR_HEAD;
        // Seems like inlined init, though based on LMDvdFileOpen it could not be?
        LMDvdFileInfo* info = LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->_7C;

        while (true) {
            s32 blockStatus;
            blockStatus = DVDGetCommandBlockStatus(&info->cb);
            if (blockStatus != DVD_COMMAND_READ) break;
        }
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo = info;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mFileBuffer = 0;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mDecompBuffer = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mArchive = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mPostLoadFunc = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallback = nullptr;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();

        OSReceiveMessage(&LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);

        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mDecompBuffer = nullptr;

        u8 oldGroupId = fn_800061B8(LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mHeapGroupID);
        void* ret = LMDvdFile::alloc(0x68, 4);
        fn_800061B8(oldGroupId);

        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mArchive = reinterpret_cast<JKRMemArchive*>(ret);
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mPostLoadFunc = mountFileFromArchive;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallback = pCallback;
        LMDvdFileQueue::sCurDvdFile.mCurrFileInfo->mCallbackArg = pCallbackArg;

        if (LMDvdFileQueue::sCurDvdFile.openFile(pFileName, pBuffer)) {
            LMDvdFileQueue::sCurDvdFile._0++;
        }

        return reinterpret_cast<u8*>(ret);
    }
}

void* LMDvdFileInfo::getCallbackArg() {
    return mCallbackArg;
}

u8* LMDvdFileInfo::getFileBuffer() {
    return mFileBuffer;
}

u32 LMDvdFileInfo::getLength() {
    return length;
}

JKRMemArchive* LMDvdFileInfo::getArchive() {
    return mArchive;
}

namespace LMDvdFile {
    s32 checkCurUnk0() {
        return LMDvdFileQueue::sCurDvdFile._0 != 0;
    }

    s32 getAllocDirection() {
        return LMDvdFileQueue::sCurDvdFile.mAllocDirection;
    }

    void checkCurDVDStatus() {
        LMDvdFileQueue::sCurDvdFile.updateDvdDriveStatus();
    }

    void closeFile(void *pMsg, LMDvdFileInfo* pInfo) {
        LMDvdFileQueue::sCurDvdFile._0--;
        DVDClose(pInfo);

        //Required to fix regalloc
        void* msg = pMsg;

        switch (DVDGetCommandBlockStatus(&pInfo->cb)) {
            case 0:
                break;
            case 10:
                pInfo->mPostLoadFunc = nullptr;
                pInfo->mCallback = nullptr;
                return;
            case -1:
                pInfo->mPostLoadFunc = nullptr;
                pInfo->mCallback = nullptr;
                return;
        }
        OSSendMessage(&pInfo->mMsgQueue, msg, OS_MESSAGE_NOBLOCK);
    }
}

void decompressFile(void* param_1, LMDvdFileInfo* pInfo) {
    //TODO: Remove this
    FORCE_DONT_INLINE

    s32 size;
    u8* src = pInfo->mFileBuffer;

    if (reinterpret_cast<LMYay0::Yay0Header*>(src)->mMagic != 'Yay0') {
        sFileDataError = 1;
        return;
    }

    size = LMYay0::getArcSize(src);

    if (pInfo->mDecompBuffer == 0) {
        fn_800061B8(pInfo->mHeapGroupID);
        pInfo->mDecompBuffer = reinterpret_cast<u8*>(LMDvdFile::alloc(size, 0x20));
    }
    u8* temp = pInfo->mDecompBuffer;

    LMYay0::decompress(src, temp);
    JKRFreeToHeap(nullptr, src);
}

inline void mountBuffer(LMDvdFileInfo* pInfo, u8* pBuffer) {
    if (reinterpret_cast<JKRArchive::SArcHeader*>(pBuffer)->signature != 'RARC') {
        sFileDataError = 1;
    } else {
        new (pInfo->mArchive) JKRMemArchive(pBuffer, 0, pInfo->mBufferBreakFlag);
    }
}

void mountFileFromArchive(void* param_1, LMDvdFileInfo* pInfo) {
    mountBuffer(pInfo, pInfo->mFileBuffer);
}

void decompressAndMountArchive(void* param_1, LMDvdFileInfo* pInfo) {
    decompressFile(param_1, pInfo);

    if (sFileDataError == 0) {
        mountBuffer(pInfo, pInfo->mDecompBuffer);
    }
}
