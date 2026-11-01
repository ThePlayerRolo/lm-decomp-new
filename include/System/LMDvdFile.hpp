#ifndef LM_DVD_FILE_HPP
#define LM_DVD_FILE_HPP

#include <JSystem/JKernel/JKRMemArchive.hpp>
#include <dolphin.h>

class JKRMemArchive;
class LMDvdFileInfo;

enum AllocDirection {
    ALLOC_DIR_TAIL = -1,
    ALLOC_DIR_HEAD = 1,
};

typedef void (*LMDvdFileInfoCallback)(void* param_1, LMDvdFileInfo* param_2);

#define MAX_FILE_INFO_ARR 64

class LMDvdFileInfo : public DVDFileInfo {
public:
    void* getCallbackArg();
    u8* getFileBuffer();
    u32 getLength();
    JKRMemArchive* getArchive();

public:
    /* 0x3C */ OSMessageQueue mMsgQueue;
    /* 0x5C */ s32 _5C;
    /* 0x60 */ s32 mAlignedFileSize;
    /* 0x64 */ u8* mFileBuffer;
    /* 0x68 */ u8* mDecompBuffer;
    /* 0x6C */ JKRMemArchive* mArchive;
    /* 0x70 */ void* mCallbackArg;
    /* 0x74 */ LMDvdFileInfoCallback mCallback;
    /* 0x78 */ LMDvdFileInfoCallback mPostLoadFunc;
    /* 0x7C */ LMDvdFileInfo* _7C;
    /* 0x80 */ u8 mHeapGroupID;
    /* 0x84 */ JKRMemBreakFlag mBufferBreakFlag;
};


namespace LMDvdFile {
    void* alloc(u32, s32);
    LMDvdFileInfo* getFileInfoRing();
    void init();
    u8* openFile(const char*, u8*);
    u8* openFile(const char*, LMDvdFileInfoCallback, u8*, void*);
    u8* openCompressedArchive(const char*, LMDvdFileInfoCallback, u8*, void*);
    u8* openCompressedArchive(const char*, u8*);
    JKRMemArchive* openMemArchive(const char*, void*);
    u8* openArchive(const char*, LMDvdFileInfoCallback, u8*, void*);

    s32 checkCurUnk0();
    s32 getAllocDirection();
    void checkDVDStatus();
    void closeFile(void*, LMDvdFileInfo*);
};

extern s32 sFileDataError;
extern void decompressFile(void*, LMDvdFileInfo*);
extern void mountFileFromArchive(void*, LMDvdFileInfo*);
extern void decompressAndMountArchive(void*, LMDvdFileInfo*);

#endif
