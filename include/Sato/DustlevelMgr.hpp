#ifndef DUST_LEVEL_MGR
#define DUST_LEVEL_MGR

#include "Koga/Message.hpp"
#include "Sato/saGrainControl.hpp"
#include "dolphin/mtx.h"

class Unk90 {
public:
    Unk90() {
        _458 = false;
    }

    void fn_8012E350();
    bool fn_8012F9C8(Unk90*);
    void fn_8012fc50();

    friend class DustlevelMgr;
private:
    u8 _00 [0x30];
    void* _30;
    u8 _34 [0x3d - 0x34];
    bool _3d;
    u8 _3e [0x140 - 0x3e];
    Unk90* _140;
    u8 _14C [0x3d8 - 0x144];
    Unk90* _3d8;
    u8 _3dc [0x450 - 0x3dc];
    /* 0x450 */ Vec** _450;
    /* 0x454 */ void* _454;
    /* 0x458 */ bool _458;
    /* 0x459 */ bool _459;
    /* 0x45c */ f32 _45c;
    /* 0x460 */ f32 _460;
    /* 0x464 */ void* _464;
    /* 0x468 */ Vec* _468;
    /* 0x46C */ Vec* _46C;
    /* 0x470 */ f32 _470;
    /* 0x474 */ u32 _474;
};

Unk90 gUnk90;

struct DustlevelParam {
    /* 0x00 */ DustlevelParam* mNext;
    /* 0x04 */ DustlevelParam* mPrev;

    /* 0x08 */ u8 _08 [0x4];
    /* 0x0C */ Vec _0C;
    /* 0x18 */ u32 _18;
    /* 0x1C */ u32 _1C;
};

struct DustlevelControl {
    /* 0x00 */ saGrainList<DustlevelParam> mParams;
    /* 0x24 */ DustlevelControl* mPrev;
    /* 0x28 */ DustlevelControl* mNext;
};

class DustlevelMgr : public MessageReceiver, public saGrainControl<DustlevelControl, DustlevelParam>  {
public:
    DustlevelMgr() {
        _90 = &gUnk90;
    };
    virtual ~DustlevelMgr() {};

    // From MessageReceiver
    virtual BOOL vt_0C(ToolDataRef*);
    virtual BOOL vt_10(ToolDataRef*);

    u32 fn_801300B8();
    void fn_801303EC();
private:
    /* 0x00 vtable */
    /* 0x04 saGrainControl */
    /* 0x90 */ Unk90* _90;
};

#endif
