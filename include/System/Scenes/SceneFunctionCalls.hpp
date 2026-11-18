#ifndef SCENE_UNK_FUNCTIONS_HPP
#define SCENE_UNK_FUNCTIONS_HPP

#include "System/Scenes/Scene.hpp"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>

class JKRMemArchive;
class J2DPicture;
class DiscFileInfo;

// externs
extern void fn_80066FAC(JKRMemArchive*);
extern void fn_80188594(void*, u32, u32);
extern void fn_8004D4C8();
extern void fn_80188714(void*);
extern void fn_80188638();
extern bool fn_80188740();
extern void fn_80009490();
extern void fn_8005FD80();
extern void fn_8003EB44();
extern void fn_8000A40C(f32, f32, f32, f32, f32, f32, Mtx, s32, s32, u32);

// SceneManager calls these, unsure of types/args
extern u8 fn_8018A8B4();
extern void fn_8018A8BC(s32);
extern void fn_80008394();
extern void fn_800083B4(s32);
extern bool fn_8018A860();
extern u32 fn_80185938();
extern void fn_8000AD48();
extern void fn_8000ADA0();
extern void fn_800081A8(void*); //Probable same TU as below
extern void fn_8000812C(void*);
extern void fn_800083A4(s32);
extern void fn_80009540(u16);
extern void fn_80185910();
extern void fn_80009580();
extern void fn_8000ADCC();
extern void fn_8018865C();
extern void fn_80188710();
extern void fn_80005E04();

// Definitely not from SceneManager's data
extern s32 lbl_804D7FF0;

// SelectScene calls these, unsure of types/args
extern void* fn_800739A4(s32);
extern void fn_800735FC();
extern void fn_800379F4(void*);
extern void fn_800626B0();
extern void fn_8004CED4();
extern SceneID fn_8004CF6C();
extern void fn_8004CFBC();
extern void fn_8004D014();

// Definitely not SelectScene's data
extern u8 lbl_803CDEB0[0xF]; //definitely some struct of X object, size is unknown
extern s32 lbl_804D8060;

// EndingScene calls these, unsure of types/args
extern void fn_80057904(u32, u32, u32);
extern void fn_80057A68();
extern void fn_80057A8C();
extern void fn_80057ACC(GXColor);
extern void fn_80057AD8(GXTexObj*, s16, s16, s16, s16, u8);
extern void fn_80188760(u32, void*); // Something for JAudio play?

// OpeningScene calls these, unsure of types/args
extern void fn_8005DAC4();
extern void fn_80188FB0(u32);
extern bool fn_80189054();
extern void fn_80115264();
extern void fn_80114A38(s32);
extern void fn_80114C00();
extern void fn_801891B4(u32);
extern s32 fn_80114C70();
extern void fn_80114E18();
extern void fn_80188D0C(u32);
extern void fn_801151DC();

// Definitely not OpeningScene's data
extern s32 lbl_804D8D18;

// StuffRollScene calls these, unsure of types/args
extern void fn_8000F728();
extern s32 fn_8000F874();
extern void fn_8000FB58();

// MovieScene calls these, unsure of types/args
extern void fn_8006722C();
extern void fn_8018C920(const char*, void*, u32); // Something to do with playing the pikmin movie
extern s32 fn_800673E0();
extern void fn_80067420();
extern void fn_8006775C();

// TitleScene calls these, unsure of types/args
extern void fn_8003ADE0(s32);
extern void fn_8018A2A0(s32);
extern s32 fn_8003AE54();
extern void fn_8000EC98();
extern void fn_8003AE7C();
extern void fn_8003AEA0();
extern void fn_80005C00();

// MainGameUtils call these, unsure of types/args
extern void* fn_800AD39C(s32); //Probably a player object, unsure
extern s32 lbl_804D8438;
extern void fn_8018A678(s32);
extern void fn_8015FD68(void*);
extern u8 lbl_803D990C[0xF]; //definitely some struct of X object, size is unknown
extern void fn_8007220C();
extern s32 lbl_804D843C;
extern void fn_80029BA4(void*, s32);
extern void fn_80121944();
extern void fn_80046864();
extern void fn_80160138(void*);
extern s32 fn_801219FC();
extern void fn_80029C38();
extern void fn_80121AFC();
extern void fn_80029FA0();
extern void fn_8002A17C();
extern void fn_801604FC(void*, Mtx*);
extern void fn_80045D18();
extern void fn_8005DF84();
extern void fn_80046868();
extern void fn_80072230(s32);
extern void fn_8003E7B0(s32);
extern bool fn_80029C08();
extern void fn_8002A1F4();
extern void fn_801219C4();
extern void fn_8005DAFC();
extern void fn_8015FD80(void*, void*);
extern void fn_800391D4();
extern s32 fn_80039304();
extern void fn_80039328();
extern void fn_800393CC();
extern void fn_800531B8();
extern void fn_80053224();
extern void fn_8005332C();
extern void fn_80055114(s32);
extern s32 fn_80055270();
extern void fn_80055294();
extern void fn_80055338();
extern void fn_80187214();
extern void fn_80187218();
extern void fn_800518A0();
extern s32 fn_800517D8();

#endif
