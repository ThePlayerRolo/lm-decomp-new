#ifndef S3DMODEL_H_
#define S3DMODEL_H_

#include <types.h>
#include <dolphin/mtx.h>

struct S3DModelInfo {
    /* 0x00 */ s32 _0;
    /* 0x04 */ s32 _4;
    /* 0x08 */ u16 _8;
    /* 0x0A */ u16 _A;
    /* 0x0C */ u16 _C;
};

class S3DModel {
public:
    S3DModel(S3DModelInfo*, s32);
    ~S3DModel();

    void init(S3DModelInfo*, s32);

public:
    /* 0x00 */ s32 _0;
    /* 0x04 */ S3DModelInfo* _4;
    /* 0x08 */ s32 _8;
    /* 0x0C */ s32 _C;
    /* 0x10 */ s32 _10;
    /* 0x14 */ void* _14;
    // size: 0x118
};

#endif
