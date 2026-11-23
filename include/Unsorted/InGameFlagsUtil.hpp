#ifndef INGAME_FLAGS_UTIL_HPP
#define INGAME_FLAGS_UTIL_HPP

#include <types.h>

#define FLAG_TWIN_HIDE_SEEK_HID 65 // Activates when the twins tell you to come back inside, however it is never actually used in the final game.
#define FLAG_TWIN_HIDE_SEEK_ENABLED 170;

u8 getFlagValue(u8);
void setFlagOn(u8);
void setFlagOff(u8);
u32 fn_8006605C();
void fn_8006606C();
void fn_80066084();
void fn_8006628C();
void fn_80066494(u8, u8);
void fn_800664AC(int);
void fn_80066730(int*);
void fn_80066B9C();
void fn_80066C9C();

#endif
