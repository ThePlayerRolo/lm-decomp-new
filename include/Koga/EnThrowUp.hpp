#ifndef ENTHROW_UP_HPP
#define ENTHROW_UP_HPP

#include "Sato/EnemyStrategy.hpp"
#include "Koga/BaseParam.hpp"
#include "Koga/ParamInst.hpp"
#include "Koga/Params.hpp"

class EnThrowUpParams {
public:
    EnThrowUpParams() :
        mParams(""),
        PARAM_INIT(sGravity, 3.0f),
        PARAM_INIT(sResistance, 0.0009f),
        PARAM_INIT(sFriction, 0.6f),
        PARAM_INIT(sReflect, 0.6f),
        PARAM_INIT(sEpsilon, 1.0f),
        PARAM_INIT(sAccelResistance, 0.5f)
    {}

    /* 0x00 */ TParams mParams;
    /* 0x0C */ TParamT<f32> sGravity;
    /* 0x20 */ TParamT<f32> sResistance;
    /* 0x34 */ TParamT<f32> sFriction;
    /* 0x48 */ TParamT<f32> sReflect;
    /* 0x5C */ TParamT<f32> sEpsilon;
    /* 0x70 */ TParamT<f32> sAccelResistance;
};

class EnThrowUp : public EnemyStrategy {
public:
    EnThrowUp() { }

    /* 0x1C */ virtual void doBehavior();
    /* 0x20 */ virtual void doBehaviorInit();

    void loadParamsFromFile(const char* pFilename);

    /* 0x14 */ EnThrowUpParams mParams;
    /* 0x84 */ u8 _84[0x90 - 0x84];
};


#endif
