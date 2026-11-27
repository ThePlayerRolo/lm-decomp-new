#ifndef EN_ZAKO_HPP
#define EN_ZAKO_HPP

#include "Koga/ToolData.hpp"
#include "Sato/EnThought.hpp"
#include "macros.h"

class EnZako : public EnThought {
public:
    EnZako();
    /* 0x08 */ virtual ~EnZako();
    /* 0x0C */ virtual void vt_0C();
    /* 0x10 */ virtual void vt_10();

    void attachPathData(const Koga::ToolData::JMapData*);
    bool attachPathData();
    Koga::ToolData* fn_800C1FF4();
    void fn_800C1FFC(); // Not sure about return type/args
    void* fn_800C211C(); // Not sure about return type/args, could be bool too?

    inline s32 getPlayerID() const { return mPlayerID; }

    /* 0x93C */ float _93C;
    /* 0x940 */ float _940;
    /* 0x944 */ float _944;
    /* 0x948 */ float _948;
    /* 0x94C */ u16 _94C;
    /* 0x94E */ u8 padding[0x2];
    /* 0x950 */ s32 mPlayerID;
    /* 0x954 */ void* _954;
    /* 0x958 */ void* _958;
    /* 0x95C */ Koga::ToolData mPathData;
};

#endif
