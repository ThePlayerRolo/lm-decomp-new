#ifndef J2DTEXTURE_K_HPP
#define J2DTEXTURE_K_HPP

#include <JSystem/J2D/J2DPicture.hpp>
#include <JSystem/JUtility/JUTTexture.hpp>

class J2DTexture_k : public J2DPicture {
public:
    J2DTexture_k(JUTTexture* pTexture);
    J2DTexture_k() { }
    virtual ~J2DTexture_k() { }

    void draw_8003AFEC(s32 x, s32 y, s32 w, s32 h, u32 color1, u32 color2, u32 color3, u32 color4);
    void draw_8003B0E8(s32 x, s32 y, s32 h, s32 w);
    void draw_8003B264(s32 x, s32 y, s32 h, s32 w);
    void draw_8003B29C(s32 x, s32 y, s32 w, s32 h, s32 texCoordLeft, s32 texCoordRight,
        s32 texCoordTop, s32 texCoordBottom, u32 color1, u32 color2, u32 color3, u32 color4);

    void draw_8003B43C(s32 x, s32 y, s32 w, s32 h, u32 color1, u32 color2, u32 color3, u32 color4);

    /* 0x15C */ GXTexObj mTextureObj;
};

#endif
