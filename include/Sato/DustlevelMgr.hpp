#ifndef DUST_LEVEL_MGR
#define DUST_LEVEL_MGR

#include <dolphin/mtx.h>

#include "Koga/Message.hpp"
#include "Sato/DustBase.hpp"
#include "Sato/saGrainControl.hpp"
#include "System/MathUtils.hpp"

class Dust : public DustBase {
public:
    Dust() {
        _458 = false;
        _459 = false;
        _45C = 0.98f;
        _460 = 0.36f;
        _464 = sGrainParams;
        _474 = 0;
        _468 = &gZeroVec;
        _46C = &gZeroVec;
        _470 = 0.0f;
    }

    void fn_8012E350();
    void fn_8012fc50();

    static GrainParam sGrainParams[5];

    friend class DustlevelMgr;
private:
    /* 0x458 */ bool _458;
    /* 0x459 */ bool _459;
    /* 0x45c */ f32 _45C;
    /* 0x460 */ f32 _460;
    /* 0x464 */ GrainParam* _464;
    /* 0x468 */ Vec* _468;
    /* 0x46C */ Vec* _46C;
    /* 0x470 */ f32 _470;
    /* 0x474 */ u32 _474;
};

Dust gUnk90;

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

// Param 2 is step dust
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
    /* 0x90 */ Dust* _90;
};

#endif
