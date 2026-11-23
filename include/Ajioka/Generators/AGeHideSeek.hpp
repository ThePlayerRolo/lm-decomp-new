#ifndef A_GE_HIDE_SEEK_HPP
#define A_GE_HIDE_SEEK_HPP

#include "JSystem/JGeometry/JGVec3.hpp"
#include "Koga/Observer.hpp"
#include "Sato/EnemyStrategy.hpp"

struct GeneratorEvent;

class AGeHideSeek : public EnemyStrategy, public Koga::Observer<GeneratorEvent, void> {
public:
    AGeHideSeek();
    virtual ~AGeHideSeek();

    // From EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From Koga::Observer
    virtual void receiveMessage(GeneratorEvent* msg);

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_1_Init();
    bool state_1_Behavior();
    bool state_2_Init();
    bool state_2_Behavior();
    bool state_3_Init();
    bool state_3_Behavior();
    bool state_4_Init();
    bool state_4_Behavior();
    bool state_5_Init();
    bool state_5_Behavior();
    bool state_6_Init();
    bool state_6_Behavior();

    /* 0x18 */ u8 mEnabledFlag;
    /* 0x19 */ u8 _19;
    /* 0x1A */ u8 _1A[0x24 - 0x1A];
    /* 0x24 */ JGeometry::TVec3f mGeneratorPos;
    /* 0x30 */ EnemyStrategy* _30[7];

};

#endif
