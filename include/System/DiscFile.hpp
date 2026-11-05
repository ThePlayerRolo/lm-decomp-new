#ifndef DISC_FILE_HPP
#define DISC_FILE_HPP

#include "dolphin/os/OSMessage.h"
#include <JSystem/JKernel/JKRMemArchive.hpp>
#include <dolphin.h>

class JKRMemArchive;
class DiscFileInfo;
struct DiscFileQueue;

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

void* allocDiscFile(u32, s32);
DiscFileInfo* getDiscFileInfoRing();
void updateDiscDriveStatus(DiscFileQueue*);
void getNextSlot(DiscFileQueue*);
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
void closeDiscFile(void*, DiscFileInfo*);

void decompressDiscFile(void*, DiscFileInfo*);
void mountDiscArchive(void*, DiscFileInfo*);
void decompressAndMountDiscArchive(void*, DiscFileInfo*);

extern s32 sFileDataError;

#endif
