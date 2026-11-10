#include "System/Yay0.hpp"
#include "dolphin/os/OSCache.h"
#include "macros.h"

s32 getYay0ArcSize(const u8* pSrc) {
    return ALIGN_NEXT(reinterpret_cast<const Yay0Header*>(pSrc)->mSize, 32);
}

// https://decomp.me/scratch/5u7XN
void decompressYay0(const u8* pSrc, u8* pDst) {
    s32 maskOffset = 0x10;
    u8* src = const_cast<u8*>(pSrc);
    u8* dst = pDst;
    s32 decompSize = READU32_BE(src, 0x4);
    s32 linkOffset = READU32_BE(src, 0x8);
    s32 dataOffset = READU32_BE(src, 0xC);

    s32 dstOffset = 0;
    u32 bitsLeft = 0;
    u32 mask;

    do {
        if (bitsLeft == 0) {
            mask = *reinterpret_cast<u32*>(src + maskOffset);
            maskOffset += 4;
            bitsLeft = 32;
        }

        if (mask & 0x80000000) {
            dst[dstOffset++] = src[dataOffset++];
        } else {
            u16 link = *reinterpret_cast<u16*>(src + linkOffset);
            linkOffset += 2;
            s32 count = link >> 12;
            if (count == 0) {
                count = src[dataOffset++] + 0x12;
            } else {
                count += 2;
            }
            
            u8* from = dst + (dstOffset - (link & 0xFFF)) - 1;
            for (; count > 0; count--) {
                dst[dstOffset] = *from;
                dstOffset++;
                from++;
            }
        }

        mask <<= 1;
        bitsLeft--;
    } while (dstOffset < decompSize);

    DCStoreRange(dst, decompSize);
}
