#ifndef DUST_LEVEL_MGR
#define DUST_LEVEL_MGR

#include "Koga/Message.hpp"
#include "Sato/saGrainControl.hpp"
#include "dolphin/mtx.h"

struct unk90 {
    u8 _00 [0x450];
    Vec* _450;
};

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
    DustlevelMgr();
    virtual ~DustlevelMgr() {};

    // From MessageReceiver
    virtual BOOL vt_0C(ToolDataRef*);
    virtual BOOL vt_10(ToolDataRef*);


    u32 fn_801300B8();
    void fn_801303EC();
private:
    /* 0x00 vtable */
    /* 0x04 saGrainControl */
    /* 0x90 */ unk90* _90; 
};

#endif
