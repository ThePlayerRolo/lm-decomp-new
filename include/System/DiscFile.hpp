#ifndef DISC_FILE_HPP
#define DISC_FILE_HPP

#include <dolphin/dvd.h>
#include <dolphin/os/OSMessage.h>

#include <JSystem/JKernel/JKRMemArchive.hpp>

struct DiscFileInfo;

enum AllocDirection {
    ALLOC_DIR_TAIL = -1,
    ALLOC_DIR_HEAD = 1,
};

typedef void (*DiscFileCallback)(void* param_1, DiscFileInfo* param_2);

#define MAX_FILE_INFO_ARR 64

struct DiscFileInfo : public DVDFileInfo {
    /* 0x3C */ OSMessageQueue mMsgQueue;
    /* 0x5C */ OSMessage mMsg;
    /* 0x60 */ s32 mAlignedFileSize;
    /* 0x64 */ u8* mFileBuffer;
    /* 0x68 */ u8* mDecompBuffer;
    /* 0x6C */ JKRMemArchive* mArchive;
    /* 0x70 */ void* mCallbackArg;
    /* 0x74 */ DiscFileCallback mCallback;
    /* 0x78 */ DiscFileCallback mPostLoadFunc;
    /* 0x7C */ DiscFileInfo* mNext;
    /* 0x80 */ u8 mHeapGroupID;
    /* 0x84 */ JKRMemBreakFlag mBufferBreakFlag;
};

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

void* allocDiscFile(u32, s32);
DiscFileInfo* getDiscFileInfoRing();
void initDiscFiles();
u8* openDiscFile(const char*, u8*);
u8* openDiscFileAsync(const char*, DiscFileCallback, u8*, void*);
u8* openCompressedArchiveAsync(const char*, DiscFileCallback, u8*, void*);
u8* openCompressedArchive(const char*, u8*);
JKRMemArchive* openMemArchive(const char*, u8*);
u8* openArchiveAsync(const char*, DiscFileCallback, u8*, void*);

void* getDiscFileCallbackArg(DiscFileInfo*);
u8* getDiscFileFileBuffer(DiscFileInfo*);
s32 getDiscFileLength(DiscFileInfo*);
JKRMemArchive* getDiscFileArchiveBuffer(DiscFileInfo*);

s32 checkDiscFileCurUnk0();
s32 getDiscFileAllocDirection();
void setDVDStatus();
void closeDiscFile(OSMessage, DiscFileInfo*);

extern s32 sFileDataError;

#endif
