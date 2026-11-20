#ifndef DUST_LEVEL_MGR
#define DUST_LEVEL_MGR

#include "Koga/Message.hpp"
#include "Sato/saGrainControl.hpp"


class DustlevelControl;
class DustlevelParam;

class DustlevelMgr : public MessageReceiver, public saGrainControl<DustlevelControl, DustlevelParam>  {
public:
    DustlevelMgr();
    virtual ~DustlevelMgr();

    // From MessageReceiver
    virtual BOOL vt_0C(ToolDataRef*);
    virtual BOOL vt_10(ToolDataRef*);
};

#endif
