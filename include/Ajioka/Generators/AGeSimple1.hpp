#ifndef A_GE_SIMPLE_1_HPP
#define A_GE_SIMPLE_1_HPP

#include "Sato/SaEnGenUtility.hpp"
class AGeSimple1 : public SaEnGenUtility {
public:
    AGeSimple1();
    virtual ~AGeSimple1();

    // From SaEnGenUtility -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From SaEnGenUtility
    virtual void receiveMessage(GeneratorEvent* msg);

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_0x106_Init();
    bool state_0x106_Behavior();
    bool state_0x107_Init();
    bool state_0x107_Behavior();
};

#endif
