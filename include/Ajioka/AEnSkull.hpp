#ifndef A_EN_SKULL_HPP
#define A_EN_SKULL_HPP

#include "Sato/EnGhostA.hpp"

class AEnSkull : public EnGhostA {
public:
    AEnSkull();
    virtual ~AEnSkull();

    // From EnGhostA -> EnemyTypicalStrategy -> EnemyStrategyDecorator -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From EnGhostA
    virtual bool EnGhostA_fn_800C8F88();

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
};

#endif
