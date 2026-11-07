#include <dolphin/os/OSMessage.h>

#include "System/DiscFile.hpp"
#include "System/Yay0.hpp"
#include "System/DiscThread.hpp"
#include "System/UnknownSystemCalls.hpp"
#include "Unsorted/GamePad.hpp"
#include "Unsorted/80005EB8.hpp"

// Possibly Fabricated.
struct DiscUnk {
    /* 0x00 */ u8 _0[0x14];
    /* 0x14 */ OSMessage mMsg;
    /* 0x18 */ u32 _18;
};

struct DiscFileQueue {
    /* 0x00 */ s32 mNumPendingFiles;
    /* 0x04 */ AllocDirection mAllocDirection;
    /* 0x08 */ DiscFileInfo* mCurrFileInfo;
};

static void updateDiscDriveStatus(DiscFileQueue*);
static void getNextSlot(DiscFileQueue*);
static bool queueOpenDiscFile(DiscFileQueue*, const char*, u8*);
static void* queueOpenDiscFileAsync(DiscFileQueue*, const char*, DiscFileCallback, u8*, void*);
static void decompressDiscFile(void*, DiscFileInfo*);
static void mountDiscArchive(void*, DiscFileInfo*);
static void decompressAndMountDiscArchive(void*, DiscFileInfo*);

static DiscFileInfo sFileInfoRing[MAX_FILE_INFO_ARR];
static DiscFileQueue sDiscFileQueue;
s32 sFileDataError;

void* allocDiscFile(u32 size, s32 align) {
    return fn_80006080(size, align);
}

DiscFileInfo* getDiscFileInfoRing() {
    return &sFileInfoRing[0];
}

void updateDiscDriveStatus(DiscFileQueue* pQueue) {
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

void getNextSlot(DiscFileQueue* pQueue) {
    // TODO Remove this
    FORCE_DONT_INLINE
    DiscFileInfo* info = pQueue->mCurrFileInfo->mNext;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    pQueue->mCurrFileInfo = info;
    pQueue->mCurrFileInfo->mFileBuffer = nullptr;
    pQueue->mCurrFileInfo->mDecompBuffer = nullptr;
    pQueue->mCurrFileInfo->mArchive = nullptr;
    pQueue->mCurrFileInfo->mPostLoadFunc = nullptr;
    pQueue->mCurrFileInfo->mCallback = nullptr;
    pQueue->mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();
    OSReceiveMessage(&pQueue->mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);
}

bool queueOpenDiscFile(DiscFileQueue* pQueue, const char* pFileName, u8* pBuffer) {
    // TODO Remove this
    FORCE_DONT_INLINE
    DiscFileInfo* info = pQueue->mCurrFileInfo;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }

    DVDOpen(const_cast<char*>(pFileName), info);

    pQueue->mCurrFileInfo->mAlignedFileSize = ALIGN_NEXT(info->length, 32);
    pQueue->mCurrFileInfo->mBufferBreakFlag = MBF_0;
    pQueue->mCurrFileInfo->mFileBuffer = pBuffer;

    sendDiscRequest(pQueue->mCurrFileInfo);
    return true;
}

// https://decomp.me/scratch/Ro97O
void* queueOpenDiscFileAsync(DiscFileQueue* pQueue, const char* pFileName, DiscFileCallback pCallback, u8* pBuffer, void* pCallbackArg) {
    // TODO Remove this
    FORCE_DONT_INLINE
    pQueue->mCurrFileInfo->mCallback = pCallback;
    pQueue->mCurrFileInfo->mCallbackArg = pCallbackArg;

    DiscFileInfo* info = pQueue->mCurrFileInfo;

    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }

    DVDOpen(const_cast<char*>(pFileName), info);
    pQueue->mCurrFileInfo->mAlignedFileSize = ALIGN_NEXT(info->length, 32);
    pQueue->mCurrFileInfo->mBufferBreakFlag = MBF_0;
    pQueue->mCurrFileInfo->mFileBuffer = pBuffer;

    sendDiscRequest(pQueue->mCurrFileInfo);
    pQueue->mNumPendingFiles++;

    return pQueue->mCurrFileInfo->mFileBuffer;
}


void initDiscFiles() {
    initDiscThread();

    DiscFileInfo* curIndex = getDiscFileInfoRing();

    sDiscFileQueue.mAllocDirection = ALLOC_DIR_HEAD;
    sDiscFileQueue.mNumPendingFiles = 0;
    sDiscFileQueue.mCurrFileInfo = getDiscFileInfoRing();

    for (s32 i = 0; i < MAX_FILE_INFO_ARR; i++) {
        curIndex->mNext = &sFileInfoRing[i + 1];
        OSInitMessageQueue(&curIndex->mMsgQueue, &curIndex->mMsg, 1);
        curIndex++;
    }

    sFileInfoRing[MAX_FILE_INFO_ARR - 1].mNext = getDiscFileInfoRing();
}

u8* openDiscFile(const char* pFileName, u8* pBuffer) {
    getNextSlot(&sDiscFileQueue);
    sDiscFileQueue.mCurrFileInfo->mCallback = nullptr;
    sDiscFileQueue.mCurrFileInfo->mCallbackArg = nullptr;

    if (queueOpenDiscFile(&sDiscFileQueue, pFileName, pBuffer)) {
        sDiscFileQueue.mNumPendingFiles++;
    }

    u32 msg;

    OSReceiveMessage(&sDiscFileQueue.mCurrFileInfo->mMsgQueue, &msg, OS_MESSAGE_BLOCK);

    return sDiscFileQueue.mCurrFileInfo->mFileBuffer;
}

//https://decomp.me/scratch/YKS45
u8* openDiscFileAsync(const char* pFileName, DiscFileCallback pCallback, u8* pBuffer, void* pCallbackArg) {
    u8* ret;

    // Seems like inlined init, though based on LMDvdFileOpen it could not be?
    DiscFileInfo* info = sDiscFileQueue.mCurrFileInfo->mNext;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    sDiscFileQueue.mCurrFileInfo = info;
    sDiscFileQueue.mCurrFileInfo->mFileBuffer = 0;
    sDiscFileQueue.mCurrFileInfo->mDecompBuffer = nullptr;
    sDiscFileQueue.mCurrFileInfo->mArchive = nullptr;
    sDiscFileQueue.mCurrFileInfo->mPostLoadFunc = nullptr;
    sDiscFileQueue.mCurrFileInfo->mCallback = nullptr;
    sDiscFileQueue.mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();

    OSReceiveMessage(&sDiscFileQueue.mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);

    sDiscFileQueue.mCurrFileInfo->mCallback = pCallback;
    sDiscFileQueue.mCurrFileInfo->mCallbackArg = pCallbackArg;

    if (queueOpenDiscFile(&sDiscFileQueue, pFileName, pBuffer)) {
        sDiscFileQueue.mNumPendingFiles++;
        ret = sDiscFileQueue.mCurrFileInfo->mFileBuffer;
    }

    return ret;
}

//https://decomp.me/scratch/KlViD
u8* openCompressedArchiveAsync(const char* pFileName, DiscFileCallback pCallback, u8* pArchiveBuffer, void* pCallbackArg) {
    // Loads a Yay0-compressed archive and attempts to unpack it before mounting it.
    sDiscFileQueue.mAllocDirection = ALLOC_DIR_TAIL;
    // Seems like inlined init, though based on LMDvdFileOpen it could not be?
    DiscFileInfo* info = sDiscFileQueue.mCurrFileInfo->mNext;

    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    sDiscFileQueue.mCurrFileInfo = info;
    sDiscFileQueue.mCurrFileInfo->mFileBuffer = 0;
    sDiscFileQueue.mCurrFileInfo->mDecompBuffer = nullptr;
    sDiscFileQueue.mCurrFileInfo->mArchive = nullptr;
    sDiscFileQueue.mCurrFileInfo->mPostLoadFunc = nullptr;
    sDiscFileQueue.mCurrFileInfo->mCallback = nullptr;
    sDiscFileQueue.mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();

    OSReceiveMessage(&sDiscFileQueue.mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);

    if (pArchiveBuffer != 0) {
        sDiscFileQueue.mCurrFileInfo->mBufferBreakFlag = MBF_0;
    }
    sDiscFileQueue.mCurrFileInfo->mDecompBuffer = pArchiveBuffer;
    u8 oldGroupId = fn_800061B8(sDiscFileQueue.mCurrFileInfo->mHeapGroupID);
    void* ret = allocDiscFile(0x68, 4);
    fn_800061B8(oldGroupId);
    sDiscFileQueue.mCurrFileInfo->mArchive = reinterpret_cast<JKRMemArchive*>(ret);
    sDiscFileQueue.mCurrFileInfo->mPostLoadFunc = decompressAndMountDiscArchive;
    sDiscFileQueue.mCurrFileInfo->mCallback = pCallback;
    sDiscFileQueue.mCurrFileInfo->mCallbackArg = pCallbackArg;

    if (queueOpenDiscFile(&sDiscFileQueue, pFileName, nullptr)) {
        sDiscFileQueue.mNumPendingFiles++;
    }
    sDiscFileQueue.mAllocDirection = ALLOC_DIR_HEAD;

    if (pArchiveBuffer != 0) {
        sDiscFileQueue.mCurrFileInfo->mBufferBreakFlag = MBF_0;
    }
    return reinterpret_cast<u8*>(ret);
}

u8* openCompressedArchive(const char* pFileName, u8* pBuffer) {
    u8* data = openCompressedArchiveAsync(pFileName, nullptr, pBuffer, nullptr);
    u32 msg;
    OSReceiveMessage(&sDiscFileQueue.mCurrFileInfo->mMsgQueue, &msg, OS_MESSAGE_BLOCK);
    return data;
}

//https://decomp.me/scratch/WwyKN
JKRMemArchive* openMemArchive(const char* pFileName, u8* pBuffer) {
    void* buffer;
    JKRMemArchive* archive;
    DiscUnk unk;

    getNextSlot(&sDiscFileQueue);
    queueOpenDiscFileAsync(&sDiscFileQueue, pFileName, nullptr, pBuffer, nullptr);

    OSReceiveMessage(&sDiscFileQueue.mCurrFileInfo->mMsgQueue, &unk.mMsg, OS_MESSAGE_BLOCK);
    buffer = sDiscFileQueue.mCurrFileInfo->mFileBuffer;

    archive = new JKRMemArchive();
    archive->mountFixed(buffer, MBF_1);
    return archive;
}

u8* openArchiveAsync(const char* pFileName, DiscFileCallback pCallback, u8* pBuffer, void* pCallbackArg) {
    // Loads an uncompressed RARC archive and mounts it directly.
    sDiscFileQueue.mAllocDirection = ALLOC_DIR_HEAD;
    // Seems like inlined init, though based on LMDvdFileOpen it could not be?
    DiscFileInfo* info = sDiscFileQueue.mCurrFileInfo->mNext;

    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    sDiscFileQueue.mCurrFileInfo = info;
    sDiscFileQueue.mCurrFileInfo->mFileBuffer = 0;
    sDiscFileQueue.mCurrFileInfo->mDecompBuffer = nullptr;
    sDiscFileQueue.mCurrFileInfo->mArchive = nullptr;
    sDiscFileQueue.mCurrFileInfo->mPostLoadFunc = nullptr;
    sDiscFileQueue.mCurrFileInfo->mCallback = nullptr;
    sDiscFileQueue.mCurrFileInfo->mHeapGroupID = getCurHeapGroupId();

    OSReceiveMessage(&sDiscFileQueue.mCurrFileInfo->mMsgQueue, nullptr, OS_MESSAGE_NOBLOCK);

    sDiscFileQueue.mCurrFileInfo->mDecompBuffer = nullptr;

    u8 oldGroupId = fn_800061B8(sDiscFileQueue.mCurrFileInfo->mHeapGroupID);
    void* ret = allocDiscFile(0x68, 4);
    fn_800061B8(oldGroupId);

    sDiscFileQueue.mCurrFileInfo->mArchive = reinterpret_cast<JKRMemArchive*>(ret);
    sDiscFileQueue.mCurrFileInfo->mPostLoadFunc = mountDiscArchive;
    sDiscFileQueue.mCurrFileInfo->mCallback = pCallback;
    sDiscFileQueue.mCurrFileInfo->mCallbackArg = pCallbackArg;

    if (queueOpenDiscFile(&sDiscFileQueue, pFileName, pBuffer)) {
        sDiscFileQueue.mNumPendingFiles++;
    }

    return reinterpret_cast<u8*>(ret);
}

void* getDiscFileCallbackArg(DiscFileInfo* pInfo) {
    return pInfo->mCallbackArg;
}

u8* getDiscFileFileBuffer(DiscFileInfo* pInfo) {
    return pInfo->mFileBuffer;
}

s32 getDiscFileLength(DiscFileInfo* pInfo) {
    return pInfo->length;
}

JKRMemArchive* getDiscFileArchiveBuffer(DiscFileInfo* pInfo) {
    return pInfo->mArchive;
}

s32 checkDiscFileCurUnk0() {
    return sDiscFileQueue.mNumPendingFiles != 0;
}

s32 getDiscFileAllocDirection() {
    return sDiscFileQueue.mAllocDirection;
}

void setDVDStatus() {
    updateDiscDriveStatus(&sDiscFileQueue);
}

void closeDiscFile(OSMessage pMsg, DiscFileInfo* pInfo) {
    sDiscFileQueue.mNumPendingFiles--;
    DVDClose(pInfo);
    OSMessage msg = pMsg;

    switch (DVDGetCommandBlockStatus(&pInfo->cb)) {
        case DVD_RESULT_GOOD:
            break;
        case DVD_STATE_CANCELED:
            pInfo->mPostLoadFunc = nullptr;
            pInfo->mCallback = nullptr;
            return;
        case DVD_RESULT_FATAL_ERROR:
            pInfo->mPostLoadFunc = nullptr;
            pInfo->mCallback = nullptr;
            return;
    }
    OSSendMessage(&pInfo->mMsgQueue, msg, OS_MESSAGE_NOBLOCK);
}

void decompressDiscFile(void* param_1, DiscFileInfo* pInfo) {
    //TODO: Remove this
    FORCE_DONT_INLINE

    s32 size;
    u8* src = pInfo->mFileBuffer;

    if (reinterpret_cast<Yay0Header*>(src)->mMagic != 'Yay0') {
        sFileDataError = 1;
        return;
    }

    size = getYay0ArcSize(src);

    if (pInfo->mDecompBuffer == 0) {
        fn_800061B8(pInfo->mHeapGroupID);
        pInfo->mDecompBuffer = reinterpret_cast<u8*>(allocDiscFile(size, 0x20));
    }
    u8* temp = pInfo->mDecompBuffer;

    decompressYay0(src, temp);
    JKRFreeToHeap(nullptr, src);
}

inline void mountBuffer(DiscFileInfo* pInfo, u8* pBuffer) {
    if (reinterpret_cast<JKRArchive::SArcHeader*>(pBuffer)->signature != 'RARC') {
        sFileDataError = 1;
    } else {
        new (pInfo->mArchive) JKRMemArchive(pBuffer, 0, pInfo->mBufferBreakFlag);
    }
}

void mountDiscArchive(void* param_1, DiscFileInfo* pInfo) {
    mountBuffer(pInfo, pInfo->mFileBuffer);
}

void decompressAndMountDiscArchive(void* param_1, DiscFileInfo* pInfo) {
    decompressDiscFile(param_1, pInfo);

    if (sFileDataError == 0) {
        mountBuffer(pInfo, pInfo->mDecompBuffer);
    }
}
