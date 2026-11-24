#pragma once

#include "JSystem/J2D/J2DPicture.hpp"

class J2DTexture_k : public J2DPicture {
public:
    J2DTexture_k() { }
    virtual ~J2DTexture_k() { }

    void draw(s32 x, s32 y, s32 h, s32 w);

    /* 0x15C */ u8 _15C[0x17C - sizeof(J2DPicture)];
};
