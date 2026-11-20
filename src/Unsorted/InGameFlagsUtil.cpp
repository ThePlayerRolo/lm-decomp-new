#include "Unsorted/InGameFlagsUtil.hpp"

struct unkStruct {
    u8 _0[0x9];
    u8 _9[0x12];
    u32 _1C;
    u8 _30[0x639]; // TODO figure out what this is

    // Every flag is a single bit
    // Flags 0-84 are savable in the mem card
    // Flags 85-169 are reset back to off/0 every time Luigi leaves the room
    // Flags 170-255 are reset back to off/0 every time Luigi changes Maps.
    u8 flags[0x20];

    u8 _683[0x98F];
    u8 _1008;
    u8 _1009[0x3];
    u32 _100C;
    u8 _1010[0x8];
    u32 _1018;
    u32 _101C;
    u32 _1020;
    u32 _1024;
    u8 _1028[0x631];
    u8 _1659[0x20];
};

unkStruct lbl_803D2D40;

u8 getFlagValue(u8 flagNum) {
    return (lbl_803D2D40.flags[flagNum / 8] >> (flagNum % 8)) & 1;
}

void setFlagOn(u8 flagNum) {
    lbl_803D2D40.flags[flagNum / 8] |= (1 << (flagNum % 8));
}

void setFlagOff(u8 flagNum) {
    lbl_803D2D40.flags[flagNum / 8] &= ~(1 << (flagNum % 8));
}

u32 fn_8006605C() {
    return lbl_803D2D40._1C;
}

void fn_8006606C() {
    lbl_803D2D40._9[0] += 1;
}

void fn_80066494(u8 param_1, u8 param_2) {
    lbl_803D2D40._9[param_1] = param_2;
}

// https://decomp.me/scratch/0UKNU
// This will more likely match up when the struct/object is not some global var.
void fn_80066B9C() {
    lbl_803D2D40._1008 = 0;
    lbl_803D2D40._101C = 0;
    lbl_803D2D40._100C = 0;
    lbl_803D2D40._1018 = 0;
    lbl_803D2D40._1020 = 0;
    lbl_803D2D40._1024 = 0;

    for (u32 i = 0; i < 256; i += 8) {
        for (u8 j = 0; j < 8; j++) {
            u8 flagAddr = j + i;
            lbl_803D2D40._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
        }
    }

}
