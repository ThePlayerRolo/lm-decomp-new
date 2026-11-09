#ifndef A_GE_SIMPLE_2_HPP
#define A_GE_SIMPLE_2_HPP

#include "Sato/SaEnGenUtility.hpp"
class AGeSimple2 : public SaEnGenUtility {
public:
    AGeSimple2();
    virtual ~AGeSimple2();

    // From SaEnGenUtility -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From SaEnGenUtility
    virtual void receiveMessage(GeneratorEvent* msg);

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_0x104_Init();
    bool state_0x104_Behavior();
    bool state_0x103_Init();
    bool state_0x103_Behavior();
    bool state_0x106_Init();
    bool state_0x106_Behavior();
    bool state_0x107_Init();
    bool state_0x107_Behavior();
};

#endif
